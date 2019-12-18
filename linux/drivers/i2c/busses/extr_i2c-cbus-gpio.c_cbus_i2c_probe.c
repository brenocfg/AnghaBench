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
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct i2c_adapter {int /*<<< orphan*/  name; int /*<<< orphan*/ * algo; int /*<<< orphan*/  timeout; int /*<<< orphan*/  nr; TYPE_1__ dev; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct cbus_host {TYPE_2__* dev; int /*<<< orphan*/  lock; void* sel; void* dat; void* clk; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  I2C_CLASS_HWMON ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cbus_i2c_algo ; 
 void* devm_gpiod_get_index (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int gpiod_count (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_set_consumer_name (void*,char*) ; 
 int i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct cbus_host*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct i2c_adapter*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int cbus_i2c_probe(struct platform_device *pdev)
{
	struct i2c_adapter *adapter;
	struct cbus_host *chost;

	adapter = devm_kzalloc(&pdev->dev, sizeof(struct i2c_adapter),
			       GFP_KERNEL);
	if (!adapter)
		return -ENOMEM;

	chost = devm_kzalloc(&pdev->dev, sizeof(*chost), GFP_KERNEL);
	if (!chost)
		return -ENOMEM;

	if (gpiod_count(&pdev->dev, NULL) != 3)
		return -ENODEV;
	chost->clk = devm_gpiod_get_index(&pdev->dev, NULL, 0, GPIOD_OUT_LOW);
	if (IS_ERR(chost->clk))
		return PTR_ERR(chost->clk);
	chost->dat = devm_gpiod_get_index(&pdev->dev, NULL, 1, GPIOD_IN);
	if (IS_ERR(chost->dat))
		return PTR_ERR(chost->dat);
	chost->sel = devm_gpiod_get_index(&pdev->dev, NULL, 2, GPIOD_OUT_HIGH);
	if (IS_ERR(chost->sel))
		return PTR_ERR(chost->sel);
	gpiod_set_consumer_name(chost->clk, "CBUS clk");
	gpiod_set_consumer_name(chost->dat, "CBUS dat");
	gpiod_set_consumer_name(chost->sel, "CBUS sel");

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

	i2c_set_adapdata(adapter, chost);
	platform_set_drvdata(pdev, adapter);

	return i2c_add_numbered_adapter(adapter);
}