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
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int txdone_poll; int txpoll_period; int num_chans; void* chans; struct device* dev; int /*<<< orphan*/ * of_xlate; int /*<<< orphan*/ * ops; } ;
struct bcm2835_mbox {TYPE_1__ controller; int /*<<< orphan*/  regs; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_mbox_chan_ops ; 
 int /*<<< orphan*/  bcm2835_mbox_index_xlate ; 
 int /*<<< orphan*/  bcm2835_mbox_irq ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_mbox_controller_register (struct device*,TYPE_1__*) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcm2835_mbox*) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm2835_mbox*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2835_mbox_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret = 0;
	struct resource *iomem;
	struct bcm2835_mbox *mbox;

	mbox = devm_kzalloc(dev, sizeof(*mbox), GFP_KERNEL);
	if (mbox == NULL)
		return -ENOMEM;
	spin_lock_init(&mbox->lock);

	ret = devm_request_irq(dev, irq_of_parse_and_map(dev->of_node, 0),
			       bcm2835_mbox_irq, 0, dev_name(dev), mbox);
	if (ret) {
		dev_err(dev, "Failed to register a mailbox IRQ handler: %d\n",
			ret);
		return -ENODEV;
	}

	iomem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mbox->regs = devm_ioremap_resource(&pdev->dev, iomem);
	if (IS_ERR(mbox->regs)) {
		ret = PTR_ERR(mbox->regs);
		dev_err(&pdev->dev, "Failed to remap mailbox regs: %d\n", ret);
		return ret;
	}

	mbox->controller.txdone_poll = true;
	mbox->controller.txpoll_period = 5;
	mbox->controller.ops = &bcm2835_mbox_chan_ops;
	mbox->controller.of_xlate = &bcm2835_mbox_index_xlate;
	mbox->controller.dev = dev;
	mbox->controller.num_chans = 1;
	mbox->controller.chans = devm_kzalloc(dev,
		sizeof(*mbox->controller.chans), GFP_KERNEL);
	if (!mbox->controller.chans)
		return -ENOMEM;

	ret = devm_mbox_controller_register(dev, &mbox->controller);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, mbox);
	dev_info(dev, "mailbox enabled\n");

	return ret;
}