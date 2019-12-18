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
struct mbox_chan {struct altera_mbox* con_priv; } ;
struct TYPE_2__ {int num_chans; int txdone_irq; int txdone_poll; int /*<<< orphan*/  txpoll_period; int /*<<< orphan*/ * ops; struct mbox_chan* chans; int /*<<< orphan*/ * dev; } ;
struct altera_mbox {scalar_t__ irq; int intr_mode; TYPE_1__ controller; scalar_t__ is_sender; int /*<<< orphan*/ * dev; int /*<<< orphan*/  mbox_base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBOX_POLLING_MS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ altera_mbox_is_sender (struct altera_mbox*) ; 
 int /*<<< orphan*/  altera_mbox_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_mbox_controller_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct altera_mbox*) ; 

__attribute__((used)) static int altera_mbox_probe(struct platform_device *pdev)
{
	struct altera_mbox *mbox;
	struct resource	*regs;
	struct mbox_chan *chans;
	int ret;

	mbox = devm_kzalloc(&pdev->dev, sizeof(*mbox),
			    GFP_KERNEL);
	if (!mbox)
		return -ENOMEM;

	/* Allocated one channel */
	chans = devm_kzalloc(&pdev->dev, sizeof(*chans), GFP_KERNEL);
	if (!chans)
		return -ENOMEM;

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	mbox->mbox_base = devm_ioremap_resource(&pdev->dev, regs);
	if (IS_ERR(mbox->mbox_base))
		return PTR_ERR(mbox->mbox_base);

	/* Check is it a sender or receiver? */
	mbox->is_sender = altera_mbox_is_sender(mbox);

	mbox->irq = platform_get_irq(pdev, 0);
	if (mbox->irq >= 0)
		mbox->intr_mode = true;

	mbox->dev = &pdev->dev;

	/* Hardware supports only one channel. */
	chans[0].con_priv = mbox;
	mbox->controller.dev = mbox->dev;
	mbox->controller.num_chans = 1;
	mbox->controller.chans = chans;
	mbox->controller.ops = &altera_mbox_ops;

	if (mbox->is_sender) {
		if (mbox->intr_mode) {
			mbox->controller.txdone_irq = true;
		} else {
			mbox->controller.txdone_poll = true;
			mbox->controller.txpoll_period = MBOX_POLLING_MS;
		}
	}

	ret = devm_mbox_controller_register(&pdev->dev, &mbox->controller);
	if (ret) {
		dev_err(&pdev->dev, "Register mailbox failed\n");
		goto err;
	}

	platform_set_drvdata(pdev, mbox);
err:
	return ret;
}