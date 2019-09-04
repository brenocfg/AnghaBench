#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct panel_drv_data {struct i2c_adapter* i2c_adapter; struct gpio_desc* hpd_gpio; int /*<<< orphan*/  hpd_lock; } ;
struct i2c_adapter {int dummy; } ;
struct gpio_desc {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct gpio_desc* devm_gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct panel_drv_data*) ; 
 int /*<<< orphan*/  dvic_hpd_isr ; 
 int /*<<< orphan*/  gpiod_to_irq (struct gpio_desc*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct i2c_adapter* of_get_i2c_adapter_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct panel_drv_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int dvic_probe_of(struct platform_device *pdev)
{
	struct panel_drv_data *ddata = platform_get_drvdata(pdev);
	struct device_node *node = pdev->dev.of_node;
	struct device_node *adapter_node;
	struct i2c_adapter *adapter;
	struct gpio_desc *gpio;
	int r;

	gpio = devm_gpiod_get_optional(&pdev->dev, "hpd", GPIOD_IN);
	if (IS_ERR(gpio)) {
		dev_err(&pdev->dev, "failed to parse HPD gpio\n");
		return PTR_ERR(gpio);
	}

	ddata->hpd_gpio = gpio;

	mutex_init(&ddata->hpd_lock);

	if (ddata->hpd_gpio) {
		r = devm_request_threaded_irq(&pdev->dev,
			gpiod_to_irq(ddata->hpd_gpio), NULL, dvic_hpd_isr,
			IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
			"DVI HPD", ddata);
		if (r)
			return r;
	}

	adapter_node = of_parse_phandle(node, "ddc-i2c-bus", 0);
	if (adapter_node) {
		adapter = of_get_i2c_adapter_by_node(adapter_node);
		of_node_put(adapter_node);
		if (adapter == NULL) {
			dev_err(&pdev->dev, "failed to parse ddc-i2c-bus\n");
			return -EPROBE_DEFER;
		}

		ddata->i2c_adapter = adapter;
	}

	return 0;
}