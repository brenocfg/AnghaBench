#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct int3496_data {int usb_id_irq; int /*<<< orphan*/  work; void* edev; void* gpio_usb_mux; void* gpio_vbus_en; void* gpio_usb_id; struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_ASIS ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  acpi_int3496_default_gpios ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_acpi_dev_add_driver_gpios (struct device*,int /*<<< orphan*/ ) ; 
 void* devm_extcon_dev_allocate (struct device*,int /*<<< orphan*/ ) ; 
 int devm_extcon_dev_register (struct device*,void*) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct int3496_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct int3496_data*) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int gpiod_to_irq (void*) ; 
 int /*<<< orphan*/  int3496_cable ; 
 int /*<<< orphan*/  int3496_do_usb_id ; 
 int /*<<< orphan*/  int3496_thread_isr ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct int3496_data*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static int int3496_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct int3496_data *data;
	int ret;

	ret = devm_acpi_dev_add_driver_gpios(dev, acpi_int3496_default_gpios);
	if (ret) {
		dev_err(dev, "can't add GPIO ACPI mapping\n");
		return ret;
	}

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->dev = dev;
	INIT_DELAYED_WORK(&data->work, int3496_do_usb_id);

	data->gpio_usb_id = devm_gpiod_get(dev, "id", GPIOD_IN);
	if (IS_ERR(data->gpio_usb_id)) {
		ret = PTR_ERR(data->gpio_usb_id);
		dev_err(dev, "can't request USB ID GPIO: %d\n", ret);
		return ret;
	}

	data->usb_id_irq = gpiod_to_irq(data->gpio_usb_id);
	if (data->usb_id_irq < 0) {
		dev_err(dev, "can't get USB ID IRQ: %d\n", data->usb_id_irq);
		return data->usb_id_irq;
	}

	data->gpio_vbus_en = devm_gpiod_get(dev, "vbus", GPIOD_ASIS);
	if (IS_ERR(data->gpio_vbus_en))
		dev_info(dev, "can't request VBUS EN GPIO\n");

	data->gpio_usb_mux = devm_gpiod_get(dev, "mux", GPIOD_ASIS);
	if (IS_ERR(data->gpio_usb_mux))
		dev_info(dev, "can't request USB MUX GPIO\n");

	/* register extcon device */
	data->edev = devm_extcon_dev_allocate(dev, int3496_cable);
	if (IS_ERR(data->edev))
		return -ENOMEM;

	ret = devm_extcon_dev_register(dev, data->edev);
	if (ret < 0) {
		dev_err(dev, "can't register extcon device: %d\n", ret);
		return ret;
	}

	ret = devm_request_threaded_irq(dev, data->usb_id_irq,
					NULL, int3496_thread_isr,
					IRQF_SHARED | IRQF_ONESHOT |
					IRQF_TRIGGER_RISING |
					IRQF_TRIGGER_FALLING,
					dev_name(dev), data);
	if (ret < 0) {
		dev_err(dev, "can't request IRQ for USB ID GPIO: %d\n", ret);
		return ret;
	}

	/* process id-pin so that we start with the right status */
	queue_delayed_work(system_wq, &data->work, 0);
	flush_delayed_work(&data->work);

	platform_set_drvdata(pdev, data);

	return 0;
}