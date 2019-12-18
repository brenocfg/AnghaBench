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
struct usb_conn_info {int id_irq; int vbus_irq; void* role_sw; void* vbus_gpiod; void* id_gpiod; void* vbus; int /*<<< orphan*/  dw_det; int /*<<< orphan*/  debounce_jiffies; struct device* dev; } ;
struct device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  USB_CONN_IRQF ; 
 int /*<<< orphan*/  USB_GPIO_DEB_MS ; 
 int /*<<< orphan*/  USB_GPIO_DEB_US ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct usb_conn_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (struct device*,char*) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_conn_info*) ; 
 int gpiod_set_debounce (void*,int /*<<< orphan*/ ) ; 
 void* gpiod_to_irq (void*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct usb_conn_info*) ; 
 int /*<<< orphan*/  usb_conn_detect_cable ; 
 int /*<<< orphan*/  usb_conn_isr ; 
 int /*<<< orphan*/  usb_conn_queue_dwork (struct usb_conn_info*,int /*<<< orphan*/ ) ; 
 void* usb_role_switch_get (struct device*) ; 
 int /*<<< orphan*/  usb_role_switch_put (void*) ; 

__attribute__((used)) static int usb_conn_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct usb_conn_info *info;
	int ret = 0;

	info = devm_kzalloc(dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->dev = dev;
	info->id_gpiod = devm_gpiod_get_optional(dev, "id", GPIOD_IN);
	if (IS_ERR(info->id_gpiod))
		return PTR_ERR(info->id_gpiod);

	info->vbus_gpiod = devm_gpiod_get_optional(dev, "vbus", GPIOD_IN);
	if (IS_ERR(info->vbus_gpiod))
		return PTR_ERR(info->vbus_gpiod);

	if (!info->id_gpiod && !info->vbus_gpiod) {
		dev_err(dev, "failed to get gpios\n");
		return -ENODEV;
	}

	if (info->id_gpiod)
		ret = gpiod_set_debounce(info->id_gpiod, USB_GPIO_DEB_US);
	if (!ret && info->vbus_gpiod)
		ret = gpiod_set_debounce(info->vbus_gpiod, USB_GPIO_DEB_US);
	if (ret < 0)
		info->debounce_jiffies = msecs_to_jiffies(USB_GPIO_DEB_MS);

	INIT_DELAYED_WORK(&info->dw_det, usb_conn_detect_cable);

	info->vbus = devm_regulator_get(dev, "vbus");
	if (IS_ERR(info->vbus)) {
		dev_err(dev, "failed to get vbus\n");
		return PTR_ERR(info->vbus);
	}

	info->role_sw = usb_role_switch_get(dev);
	if (IS_ERR(info->role_sw)) {
		if (PTR_ERR(info->role_sw) != -EPROBE_DEFER)
			dev_err(dev, "failed to get role switch\n");

		return PTR_ERR(info->role_sw);
	}

	if (info->id_gpiod) {
		info->id_irq = gpiod_to_irq(info->id_gpiod);
		if (info->id_irq < 0) {
			dev_err(dev, "failed to get ID IRQ\n");
			ret = info->id_irq;
			goto put_role_sw;
		}

		ret = devm_request_threaded_irq(dev, info->id_irq, NULL,
						usb_conn_isr, USB_CONN_IRQF,
						pdev->name, info);
		if (ret < 0) {
			dev_err(dev, "failed to request ID IRQ\n");
			goto put_role_sw;
		}
	}

	if (info->vbus_gpiod) {
		info->vbus_irq = gpiod_to_irq(info->vbus_gpiod);
		if (info->vbus_irq < 0) {
			dev_err(dev, "failed to get VBUS IRQ\n");
			ret = info->vbus_irq;
			goto put_role_sw;
		}

		ret = devm_request_threaded_irq(dev, info->vbus_irq, NULL,
						usb_conn_isr, USB_CONN_IRQF,
						pdev->name, info);
		if (ret < 0) {
			dev_err(dev, "failed to request VBUS IRQ\n");
			goto put_role_sw;
		}
	}

	platform_set_drvdata(pdev, info);

	/* Perform initial detection */
	usb_conn_queue_dwork(info, 0);

	return 0;

put_role_sw:
	usb_role_switch_put(info->role_sw);
	return ret;
}