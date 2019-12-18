#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct i2c_adapter {int nr; int /*<<< orphan*/ * quirks; TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct stu300_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  virtbase; struct i2c_adapter adapter; int /*<<< orphan*/  cmd_err; int /*<<< orphan*/  cmd_event; int /*<<< orphan*/  cmd_issue_lock; struct platform_device* pdev; int /*<<< orphan*/  clk; int /*<<< orphan*/  speed; } ;
struct resource {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {int id; TYPE_2__ dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DEPRECATED ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAME ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STU300_ERROR_NONE ; 
 int /*<<< orphan*/  STU300_EVENT_NONE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct stu300_dev* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stu300_dev*) ; 
 int i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct stu300_dev*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stu300_dev*) ; 
 int /*<<< orphan*/  scl_frequency ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stu300_algo ; 
 int stu300_init_hw (struct stu300_dev*) ; 
 int /*<<< orphan*/  stu300_irh ; 
 int /*<<< orphan*/  stu300_quirks ; 

__attribute__((used)) static int stu300_probe(struct platform_device *pdev)
{
	struct stu300_dev *dev;
	struct i2c_adapter *adap;
	struct resource *res;
	int bus_nr;
	int ret = 0;

	dev = devm_kzalloc(&pdev->dev, sizeof(struct stu300_dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	bus_nr = pdev->id;
	dev->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(dev->clk)) {
		dev_err(&pdev->dev, "could not retrieve i2c bus clock\n");
		return PTR_ERR(dev->clk);
	}

	dev->pdev = pdev;
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dev->virtbase = devm_ioremap_resource(&pdev->dev, res);
	dev_dbg(&pdev->dev, "initialize bus device I2C%d on virtual "
		"base %p\n", bus_nr, dev->virtbase);
	if (IS_ERR(dev->virtbase))
		return PTR_ERR(dev->virtbase);

	dev->irq = platform_get_irq(pdev, 0);
	ret = devm_request_irq(&pdev->dev, dev->irq, stu300_irh, 0, NAME, dev);
	if (ret < 0)
		return ret;

	dev->speed = scl_frequency;

	clk_prepare_enable(dev->clk);
	ret = stu300_init_hw(dev);
	clk_disable(dev->clk);
	if (ret != 0) {
		dev_err(&dev->pdev->dev, "error initializing hardware.\n");
		return -EIO;
	}

	/* IRQ event handling initialization */
	spin_lock_init(&dev->cmd_issue_lock);
	dev->cmd_event = STU300_EVENT_NONE;
	dev->cmd_err = STU300_ERROR_NONE;

	adap = &dev->adapter;
	adap->owner = THIS_MODULE;
	/* DDC class but actually often used for more generic I2C */
	adap->class = I2C_CLASS_DEPRECATED;
	strlcpy(adap->name, "ST Microelectronics DDC I2C adapter",
		sizeof(adap->name));
	adap->nr = bus_nr;
	adap->algo = &stu300_algo;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;
	adap->quirks = &stu300_quirks;

	i2c_set_adapdata(adap, dev);

	/* i2c device drivers may be active on return from add_adapter() */
	ret = i2c_add_numbered_adapter(adap);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, dev);
	dev_info(&pdev->dev, "ST DDC I2C @ %p, irq %d\n",
		 dev->virtbase, dev->irq);

	return 0;
}