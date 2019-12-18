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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mbox_chan {struct a37xx_mbox* con_priv; } ;
struct TYPE_2__ {int num_chans; int txdone_irq; int /*<<< orphan*/ * ops; struct mbox_chan* chans; int /*<<< orphan*/ * dev; } ;
struct a37xx_mbox {scalar_t__ irq; TYPE_1__ controller; int /*<<< orphan*/ * dev; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a37xx_mbox_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_mbox_controller_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct a37xx_mbox*) ; 

__attribute__((used)) static int armada_37xx_mbox_probe(struct platform_device *pdev)
{
	struct a37xx_mbox *mbox;
	struct resource *regs;
	struct mbox_chan *chans;
	int ret;

	mbox = devm_kzalloc(&pdev->dev, sizeof(*mbox), GFP_KERNEL);
	if (!mbox)
		return -ENOMEM;

	/* Allocated one channel */
	chans = devm_kzalloc(&pdev->dev, sizeof(*chans), GFP_KERNEL);
	if (!chans)
		return -ENOMEM;

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	mbox->base = devm_ioremap_resource(&pdev->dev, regs);
	if (IS_ERR(mbox->base)) {
		dev_err(&pdev->dev, "ioremap failed\n");
		return PTR_ERR(mbox->base);
	}

	mbox->irq = platform_get_irq(pdev, 0);
	if (mbox->irq < 0) {
		dev_err(&pdev->dev, "Cannot get irq\n");
		return mbox->irq;
	}

	mbox->dev = &pdev->dev;

	/* Hardware supports only one channel. */
	chans[0].con_priv = mbox;
	mbox->controller.dev = mbox->dev;
	mbox->controller.num_chans = 1;
	mbox->controller.chans = chans;
	mbox->controller.ops = &a37xx_mbox_ops;
	mbox->controller.txdone_irq = true;

	ret = devm_mbox_controller_register(mbox->dev, &mbox->controller);
	if (ret) {
		dev_err(&pdev->dev, "Could not register mailbox controller\n");
		return ret;
	}

	platform_set_drvdata(pdev, mbox);
	return ret;
}