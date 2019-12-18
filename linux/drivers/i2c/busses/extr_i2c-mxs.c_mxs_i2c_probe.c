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
struct platform_device_id {int /*<<< orphan*/  driver_data; } ;
struct device {scalar_t__ of_node; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  id; } ;
struct of_device_id {struct platform_device_id* data; } ;
struct TYPE_2__ {scalar_t__ of_node; struct device* parent; } ;
struct i2c_adapter {TYPE_1__ dev; int /*<<< orphan*/  nr; int /*<<< orphan*/ * quirks; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct mxs_i2c_dev {scalar_t__ regs; struct i2c_adapter adapter; int /*<<< orphan*/  dmach; int /*<<< orphan*/  cmd_complete; struct device* dev; int /*<<< orphan*/  dev_type; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 scalar_t__ MXS_I2C_CTRL0_SET ; 
 int /*<<< orphan*/  MXS_I2C_CTRL0_SFTRST ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct mxs_i2c_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mxs_i2c_dev*) ; 
 int /*<<< orphan*/  dma_request_slave_channel (struct device*,char*) ; 
 int i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct mxs_i2c_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxs_i2c_algo ; 
 int /*<<< orphan*/  mxs_i2c_dt_ids ; 
 int mxs_i2c_get_ofdata (struct mxs_i2c_dev*) ; 
 int /*<<< orphan*/  mxs_i2c_isr ; 
 int /*<<< orphan*/  mxs_i2c_quirks ; 
 int mxs_i2c_reset (struct mxs_i2c_dev*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mxs_i2c_dev*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mxs_i2c_probe(struct platform_device *pdev)
{
	const struct of_device_id *of_id =
				of_match_device(mxs_i2c_dt_ids, &pdev->dev);
	struct device *dev = &pdev->dev;
	struct mxs_i2c_dev *i2c;
	struct i2c_adapter *adap;
	int err, irq;

	i2c = devm_kzalloc(dev, sizeof(*i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	if (of_id) {
		const struct platform_device_id *device_id = of_id->data;
		i2c->dev_type = device_id->driver_data;
	}

	i2c->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(i2c->regs))
		return PTR_ERR(i2c->regs);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	err = devm_request_irq(dev, irq, mxs_i2c_isr, 0, dev_name(dev), i2c);
	if (err)
		return err;

	i2c->dev = dev;

	init_completion(&i2c->cmd_complete);

	if (dev->of_node) {
		err = mxs_i2c_get_ofdata(i2c);
		if (err)
			return err;
	}

	/* Setup the DMA */
	i2c->dmach = dma_request_slave_channel(dev, "rx-tx");
	if (!i2c->dmach) {
		dev_err(dev, "Failed to request dma\n");
		return -ENODEV;
	}

	platform_set_drvdata(pdev, i2c);

	/* Do reset to enforce correct startup after pinmuxing */
	err = mxs_i2c_reset(i2c);
	if (err)
		return err;

	adap = &i2c->adapter;
	strlcpy(adap->name, "MXS I2C adapter", sizeof(adap->name));
	adap->owner = THIS_MODULE;
	adap->algo = &mxs_i2c_algo;
	adap->quirks = &mxs_i2c_quirks;
	adap->dev.parent = dev;
	adap->nr = pdev->id;
	adap->dev.of_node = pdev->dev.of_node;
	i2c_set_adapdata(adap, i2c);
	err = i2c_add_numbered_adapter(adap);
	if (err) {
		writel(MXS_I2C_CTRL0_SFTRST,
				i2c->regs + MXS_I2C_CTRL0_SET);
		return err;
	}

	return 0;
}