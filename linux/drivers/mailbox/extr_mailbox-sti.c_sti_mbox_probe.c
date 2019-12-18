#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sti_mbox_pdata {int dummy; } ;
struct sti_mbox_device {int /*<<< orphan*/  name; TYPE_1__* dev; int /*<<< orphan*/  lock; struct mbox_controller* mbox; int /*<<< orphan*/  base; } ;
struct resource {int dummy; } ;
struct TYPE_9__ {struct sti_mbox_pdata* platform_data; struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct mbox_controller {int txdone_irq; int txdone_poll; int txpoll_period; int /*<<< orphan*/  num_chans; struct mbox_chan* chans; int /*<<< orphan*/  of_xlate; TYPE_1__* dev; int /*<<< orphan*/ * ops; } ;
struct mbox_chan {int dummy; } ;
struct device_node {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STI_MBOX_CHAN_MAX ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct mbox_chan* devm_kcalloc (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_mbox_controller_register (TYPE_1__*,struct mbox_controller*) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sti_mbox_device*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int of_property_read_string (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sti_mbox_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sti_mailbox_match ; 
 int /*<<< orphan*/  sti_mbox_irq_handler ; 
 int /*<<< orphan*/  sti_mbox_ops ; 
 int /*<<< orphan*/  sti_mbox_thread_handler ; 
 int /*<<< orphan*/  sti_mbox_xlate ; 

__attribute__((used)) static int sti_mbox_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	struct mbox_controller *mbox;
	struct sti_mbox_device *mdev;
	struct device_node *np = pdev->dev.of_node;
	struct mbox_chan *chans;
	struct resource *res;
	int irq;
	int ret;

	match = of_match_device(sti_mailbox_match, &pdev->dev);
	if (!match) {
		dev_err(&pdev->dev, "No configuration found\n");
		return -ENODEV;
	}
	pdev->dev.platform_data = (struct sti_mbox_pdata *) match->data;

	mdev = devm_kzalloc(&pdev->dev, sizeof(*mdev), GFP_KERNEL);
	if (!mdev)
		return -ENOMEM;

	platform_set_drvdata(pdev, mdev);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mdev->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mdev->base))
		return PTR_ERR(mdev->base);

	ret = of_property_read_string(np, "mbox-name", &mdev->name);
	if (ret)
		mdev->name = np->full_name;

	mbox = devm_kzalloc(&pdev->dev, sizeof(*mbox), GFP_KERNEL);
	if (!mbox)
		return -ENOMEM;

	chans = devm_kcalloc(&pdev->dev,
			     STI_MBOX_CHAN_MAX, sizeof(*chans), GFP_KERNEL);
	if (!chans)
		return -ENOMEM;

	mdev->dev		= &pdev->dev;
	mdev->mbox		= mbox;

	spin_lock_init(&mdev->lock);

	/* STi Mailbox does not have a Tx-Done or Tx-Ready IRQ */
	mbox->txdone_irq	= false;
	mbox->txdone_poll	= true;
	mbox->txpoll_period	= 100;
	mbox->ops		= &sti_mbox_ops;
	mbox->dev		= mdev->dev;
	mbox->of_xlate		= sti_mbox_xlate;
	mbox->chans		= chans;
	mbox->num_chans		= STI_MBOX_CHAN_MAX;

	ret = devm_mbox_controller_register(&pdev->dev, mbox);
	if (ret)
		return ret;

	/* It's okay for Tx Mailboxes to not supply IRQs */
	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_info(&pdev->dev,
			 "%s: Registered Tx only Mailbox\n", mdev->name);
		return 0;
	}

	ret = devm_request_threaded_irq(&pdev->dev, irq,
					sti_mbox_irq_handler,
					sti_mbox_thread_handler,
					IRQF_ONESHOT, mdev->name, mdev);
	if (ret) {
		dev_err(&pdev->dev, "Can't claim IRQ %d\n", irq);
		return -EINVAL;
	}

	dev_info(&pdev->dev, "%s: Registered Tx/Rx Mailbox\n", mdev->name);

	return 0;
}