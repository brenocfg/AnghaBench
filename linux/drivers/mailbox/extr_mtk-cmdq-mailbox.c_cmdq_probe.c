#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_6__ {int num_chans; int txdone_irq; int txdone_poll; TYPE_1__* chans; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * ops; struct device* dev; } ;
struct cmdq {int thread_nr; scalar_t__ clock; TYPE_3__ mbox; TYPE_2__* thread; scalar_t__ base; int /*<<< orphan*/  irq; int /*<<< orphan*/  irq_mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  task_busy_list; scalar_t__ base; } ;
struct TYPE_4__ {void* con_priv; } ;

/* Variables and functions */
 scalar_t__ CMDQ_THR_BASE ; 
 int CMDQ_THR_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ clk_prepare (scalar_t__) ; 
 int /*<<< orphan*/  cmdq_init (struct cmdq*) ; 
 int /*<<< orphan*/  cmdq_irq_handler ; 
 int /*<<< orphan*/  cmdq_mbox_chan_ops ; 
 int /*<<< orphan*/  cmdq_xlate ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 scalar_t__ devm_clk_get (struct device*,char*) ; 
 scalar_t__ devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct cmdq* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_mbox_controller_register (struct device*,TYPE_3__*) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct cmdq*) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cmdq*) ; 

__attribute__((used)) static int cmdq_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct cmdq *cmdq;
	int err, i;

	cmdq = devm_kzalloc(dev, sizeof(*cmdq), GFP_KERNEL);
	if (!cmdq)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	cmdq->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(cmdq->base)) {
		dev_err(dev, "failed to ioremap gce\n");
		return PTR_ERR(cmdq->base);
	}

	cmdq->irq = platform_get_irq(pdev, 0);
	if (!cmdq->irq) {
		dev_err(dev, "failed to get irq\n");
		return -EINVAL;
	}

	cmdq->thread_nr = (u32)(unsigned long)of_device_get_match_data(dev);
	cmdq->irq_mask = GENMASK(cmdq->thread_nr - 1, 0);
	err = devm_request_irq(dev, cmdq->irq, cmdq_irq_handler, IRQF_SHARED,
			       "mtk_cmdq", cmdq);
	if (err < 0) {
		dev_err(dev, "failed to register ISR (%d)\n", err);
		return err;
	}

	dev_dbg(dev, "cmdq device: addr:0x%p, va:0x%p, irq:%d\n",
		dev, cmdq->base, cmdq->irq);

	cmdq->clock = devm_clk_get(dev, "gce");
	if (IS_ERR(cmdq->clock)) {
		dev_err(dev, "failed to get gce clk\n");
		return PTR_ERR(cmdq->clock);
	}

	cmdq->mbox.dev = dev;
	cmdq->mbox.chans = devm_kcalloc(dev, cmdq->thread_nr,
					sizeof(*cmdq->mbox.chans), GFP_KERNEL);
	if (!cmdq->mbox.chans)
		return -ENOMEM;

	cmdq->mbox.num_chans = cmdq->thread_nr;
	cmdq->mbox.ops = &cmdq_mbox_chan_ops;
	cmdq->mbox.of_xlate = cmdq_xlate;

	/* make use of TXDONE_BY_ACK */
	cmdq->mbox.txdone_irq = false;
	cmdq->mbox.txdone_poll = false;

	cmdq->thread = devm_kcalloc(dev, cmdq->thread_nr,
					sizeof(*cmdq->thread), GFP_KERNEL);
	if (!cmdq->thread)
		return -ENOMEM;

	for (i = 0; i < cmdq->thread_nr; i++) {
		cmdq->thread[i].base = cmdq->base + CMDQ_THR_BASE +
				CMDQ_THR_SIZE * i;
		INIT_LIST_HEAD(&cmdq->thread[i].task_busy_list);
		cmdq->mbox.chans[i].con_priv = (void *)&cmdq->thread[i];
	}

	err = devm_mbox_controller_register(dev, &cmdq->mbox);
	if (err < 0) {
		dev_err(dev, "failed to register mailbox: %d\n", err);
		return err;
	}

	platform_set_drvdata(pdev, cmdq);
	WARN_ON(clk_prepare(cmdq->clock) < 0);

	cmdq_init(cmdq);

	return 0;
}