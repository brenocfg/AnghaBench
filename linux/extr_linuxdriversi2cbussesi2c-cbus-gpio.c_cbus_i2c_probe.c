#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  id; } ;
struct i2c_cbus_platform_data {void* sel_gpio; void* dat_gpio; void* clk_gpio; } ;
struct TYPE_5__ {struct device_node* of_node; TYPE_2__* parent; } ;
struct i2c_adapter {int /*<<< orphan*/  name; int /*<<< orphan*/ * algo; int /*<<< orphan*/  timeout; int /*<<< orphan*/  nr; TYPE_1__ dev; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct device_node {int dummy; } ;
struct cbus_host {void* sel_gpio; void* dat_gpio; void* clk_gpio; TYPE_2__* dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_IN ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  I2C_CLASS_HWMON ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cbus_i2c_algo ; 
 struct i2c_cbus_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int devm_gpio_request_one (TYPE_2__*,void*,int /*<<< orphan*/ ,char*) ; 
 void* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct cbus_host*) ; 
 void* of_get_gpio (struct device_node*,int) ; 
 int of_gpio_count (struct device_node*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct i2c_adapter*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int cbus_i2c_probe(struct platform_device *pdev)
{
	struct i2c_adapter *adapter;
	struct cbus_host *chost;
	int ret;

	adapter = devm_kzalloc(&pdev->dev, sizeof(struct i2c_adapter),
			       GFP_KERNEL);
	if (!adapter)
		return -ENOMEM;

	chost = devm_kzalloc(&pdev->dev, sizeof(*chost), GFP_KERNEL);
	if (!chost)
		return -ENOMEM;

	if (pdev->dev.of_node) {
		struct device_node *dnode = pdev->dev.of_node;
		if (of_gpio_count(dnode) != 3)
			return -ENODEV;
		chost->clk_gpio = of_get_gpio(dnode, 0);
		chost->dat_gpio = of_get_gpio(dnode, 1);
		chost->sel_gpio = of_get_gpio(dnode, 2);
	} else if (dev_get_platdata(&pdev->dev)) {
		struct i2c_cbus_platform_data *pdata =
			dev_get_platdata(&pdev->dev);
		chost->clk_gpio = pdata->clk_gpio;
		chost->dat_gpio = pdata->dat_gpio;
		chost->sel_gpio = pdata->sel_gpio;
	} else {
		return -ENODEV;
	}

	adapter->owner		= THIS_MODULE;
	adapter->class		= I2C_CLASS_HWMON;
	adapter->dev.parent	= &pdev->dev;
	adapter->dev.of_node	= pdev->dev.of_node;
	adapter->nr		= pdev->id;
	adapter->timeout	= HZ;
	adapter->algo		= &cbus_i2c_algo;
	strlcpy(adapter->name, "CBUS I2C adapter", sizeof(adapter->name));

	spin_lock_init(&chost->lock);
	chost->dev = &pdev->dev;

	ret = devm_gpio_request_one(&pdev->dev, chost->clk_gpio,
				    GPIOF_OUT_INIT_LOW, "CBUS clk");
	if (ret)
		return ret;

	ret = devm_gpio_request_one(&pdev->dev, chost->dat_gpio, GPIOF_IN,
				    "CBUS data");
	if (ret)
		return ret;

	ret = devm_gpio_request_one(&pdev->dev, chost->sel_gpio,
				    GPIOF_OUT_INIT_HIGH, "CBUS sel");
	if (ret)
		return ret;

	i2c_set_adapdata(adapter, chost);
	platform_set_drvdata(pdev, adapter);

	return i2c_add_numbered_adapter(adapter);
}