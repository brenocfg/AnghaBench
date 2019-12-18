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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mbox_chan {void* con_priv; } ;
struct TYPE_2__ {unsigned long num_chans; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * ops; struct mbox_chan* chans; struct device* dev; } ;
struct hi3660_mbox {TYPE_1__ controller; struct mbox_chan* chan; struct device* dev; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 unsigned long MBOX_CHAN_MAX ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct hi3660_mbox* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_mbox_controller_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  hi3660_mbox_ops ; 
 int /*<<< orphan*/  hi3660_mbox_xlate ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hi3660_mbox*) ; 

__attribute__((used)) static int hi3660_mbox_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hi3660_mbox *mbox;
	struct mbox_chan *chan;
	struct resource *res;
	unsigned long ch;
	int err;

	mbox = devm_kzalloc(dev, sizeof(*mbox), GFP_KERNEL);
	if (!mbox)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mbox->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(mbox->base))
		return PTR_ERR(mbox->base);

	mbox->dev = dev;
	mbox->controller.dev = dev;
	mbox->controller.chans = mbox->chan;
	mbox->controller.num_chans = MBOX_CHAN_MAX;
	mbox->controller.ops = &hi3660_mbox_ops;
	mbox->controller.of_xlate = hi3660_mbox_xlate;

	/* Initialize mailbox channel data */
	chan = mbox->chan;
	for (ch = 0; ch < MBOX_CHAN_MAX; ch++)
		chan[ch].con_priv = (void *)ch;

	err = devm_mbox_controller_register(dev, &mbox->controller);
	if (err) {
		dev_err(dev, "Failed to register mailbox %d\n", err);
		return err;
	}

	platform_set_drvdata(pdev, mbox);
	dev_info(dev, "Mailbox enabled\n");
	return 0;
}