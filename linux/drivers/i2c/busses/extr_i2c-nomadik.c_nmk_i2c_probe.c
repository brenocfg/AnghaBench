#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_12__ {TYPE_4__* parent; struct device_node* of_node; } ;
struct i2c_adapter {int /*<<< orphan*/  name; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * algo; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; TYPE_1__ dev; } ;
struct nmk_i2c_dev {scalar_t__ tft; scalar_t__ rft; int /*<<< orphan*/  clk; int /*<<< orphan*/  virtbase; int /*<<< orphan*/  timeout; struct i2c_adapter adap; int /*<<< orphan*/  irq; struct amba_device* adev; struct i2c_vendor_data* vendor; } ;
struct i2c_vendor_data {int fifodepth; } ;
struct device_node {int dummy; } ;
struct amba_id {struct i2c_vendor_data* data; } ;
struct TYPE_14__ {struct device_node* of_node; } ;
struct TYPE_13__ {int /*<<< orphan*/  start; } ;
struct amba_device {TYPE_4__ dev; TYPE_2__ res; int /*<<< orphan*/ * irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DEPRECATED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  amba_set_drvdata (struct amba_device*,struct nmk_i2c_dev*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_4__*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nmk_i2c_dev* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nmk_i2c_dev*) ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_irq_handler ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct nmk_i2c_dev*) ; 
 int /*<<< orphan*/  init_hw (struct nmk_i2c_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nmk_i2c_algo ; 
 int /*<<< orphan*/  nmk_i2c_of_probe (struct device_node*,struct nmk_i2c_dev*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_4__*) ; 
 int /*<<< orphan*/  resource_size (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,TYPE_2__*) ; 

__attribute__((used)) static int nmk_i2c_probe(struct amba_device *adev, const struct amba_id *id)
{
	int ret = 0;
	struct device_node *np = adev->dev.of_node;
	struct nmk_i2c_dev	*dev;
	struct i2c_adapter *adap;
	struct i2c_vendor_data *vendor = id->data;
	u32 max_fifo_threshold = (vendor->fifodepth / 2) - 1;

	dev = devm_kzalloc(&adev->dev, sizeof(struct nmk_i2c_dev), GFP_KERNEL);
	if (!dev) {
		dev_err(&adev->dev, "cannot allocate memory\n");
		ret = -ENOMEM;
		goto err_no_mem;
	}
	dev->vendor = vendor;
	dev->adev = adev;
	nmk_i2c_of_probe(np, dev);

	if (dev->tft > max_fifo_threshold) {
		dev_warn(&adev->dev, "requested TX FIFO threshold %u, adjusted down to %u\n",
			 dev->tft, max_fifo_threshold);
		dev->tft = max_fifo_threshold;
	}

	if (dev->rft > max_fifo_threshold) {
		dev_warn(&adev->dev, "requested RX FIFO threshold %u, adjusted down to %u\n",
			dev->rft, max_fifo_threshold);
		dev->rft = max_fifo_threshold;
	}

	amba_set_drvdata(adev, dev);

	dev->virtbase = devm_ioremap(&adev->dev, adev->res.start,
				resource_size(&adev->res));
	if (!dev->virtbase) {
		ret = -ENOMEM;
		goto err_no_mem;
	}

	dev->irq = adev->irq[0];
	ret = devm_request_irq(&adev->dev, dev->irq, i2c_irq_handler, 0,
				DRIVER_NAME, dev);
	if (ret) {
		dev_err(&adev->dev, "cannot claim the irq %d\n", dev->irq);
		goto err_no_mem;
	}

	dev->clk = devm_clk_get(&adev->dev, NULL);
	if (IS_ERR(dev->clk)) {
		dev_err(&adev->dev, "could not get i2c clock\n");
		ret = PTR_ERR(dev->clk);
		goto err_no_mem;
	}

	ret = clk_prepare_enable(dev->clk);
	if (ret) {
		dev_err(&adev->dev, "can't prepare_enable clock\n");
		goto err_no_mem;
	}

	init_hw(dev);

	adap = &dev->adap;
	adap->dev.of_node = np;
	adap->dev.parent = &adev->dev;
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_DEPRECATED;
	adap->algo = &nmk_i2c_algo;
	adap->timeout = msecs_to_jiffies(dev->timeout);
	snprintf(adap->name, sizeof(adap->name),
		 "Nomadik I2C at %pR", &adev->res);

	i2c_set_adapdata(adap, dev);

	dev_info(&adev->dev,
		 "initialize %s on virtual base %p\n",
		 adap->name, dev->virtbase);

	ret = i2c_add_adapter(adap);
	if (ret)
		goto err_no_adap;

	pm_runtime_put(&adev->dev);

	return 0;

 err_no_adap:
	clk_disable_unprepare(dev->clk);
 err_no_mem:

	return ret;
}