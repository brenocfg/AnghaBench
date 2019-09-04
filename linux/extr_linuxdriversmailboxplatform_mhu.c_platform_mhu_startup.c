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
typedef  int /*<<< orphan*/  u32 ;
struct platform_mhu_link {int /*<<< orphan*/  irq; scalar_t__ tx_reg; } ;
struct mbox_chan {TYPE_1__* mbox; struct platform_mhu_link* con_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ INTR_CLR_OFS ; 
 scalar_t__ INTR_STAT_OFS ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_mhu_rx_interrupt ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mbox_chan*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int platform_mhu_startup(struct mbox_chan *chan)
{
	struct platform_mhu_link *mlink = chan->con_priv;
	u32 val;
	int ret;

	val = readl_relaxed(mlink->tx_reg + INTR_STAT_OFS);
	writel_relaxed(val, mlink->tx_reg + INTR_CLR_OFS);

	ret = request_irq(mlink->irq, platform_mhu_rx_interrupt,
			  IRQF_SHARED, "platform_mhu_link", chan);
	if (ret) {
		dev_err(chan->mbox->dev,
			"Unable to acquire IRQ %d\n", mlink->irq);
		return ret;
	}

	return 0;
}