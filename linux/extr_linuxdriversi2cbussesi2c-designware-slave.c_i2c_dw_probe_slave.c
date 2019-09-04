#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct i2c_adapter {int retries; TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; } ;
struct dw_i2c_dev {int (* init ) (struct dw_i2c_dev*) ;int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  disable_int; int /*<<< orphan*/  disable; int /*<<< orphan*/  cmd_complete; struct i2c_adapter adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dw_i2c_dev*) ; 
 int i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_dw_algo ; 
 int /*<<< orphan*/  i2c_dw_disable ; 
 int /*<<< orphan*/  i2c_dw_disable_int ; 
 int i2c_dw_init_slave (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_dw_isr_slave ; 
 int i2c_dw_set_reg_access (struct dw_i2c_dev*) ; 
 int i2c_dw_set_sda_hold (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 int stub1 (struct dw_i2c_dev*) ; 

int i2c_dw_probe_slave(struct dw_i2c_dev *dev)
{
	struct i2c_adapter *adap = &dev->adapter;
	int ret;

	init_completion(&dev->cmd_complete);

	dev->init = i2c_dw_init_slave;
	dev->disable = i2c_dw_disable;
	dev->disable_int = i2c_dw_disable_int;

	ret = i2c_dw_set_reg_access(dev);
	if (ret)
		return ret;

	ret = i2c_dw_set_sda_hold(dev);
	if (ret)
		return ret;

	ret = dev->init(dev);
	if (ret)
		return ret;

	snprintf(adap->name, sizeof(adap->name),
		 "Synopsys DesignWare I2C Slave adapter");
	adap->retries = 3;
	adap->algo = &i2c_dw_algo;
	adap->dev.parent = dev->dev;
	i2c_set_adapdata(adap, dev);

	ret = devm_request_irq(dev->dev, dev->irq, i2c_dw_isr_slave,
			       IRQF_SHARED, dev_name(dev->dev), dev);
	if (ret) {
		dev_err(dev->dev, "failure requesting irq %i: %d\n",
			dev->irq, ret);
		return ret;
	}

	ret = i2c_add_numbered_adapter(adap);
	if (ret)
		dev_err(dev->dev, "failure adding adapter: %d\n", ret);

	return ret;
}