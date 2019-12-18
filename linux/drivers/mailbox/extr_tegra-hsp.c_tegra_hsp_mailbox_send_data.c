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
struct TYPE_2__ {struct tegra_hsp* hsp; } ;
struct tegra_hsp_mailbox {scalar_t__ index; TYPE_1__ channel; int /*<<< orphan*/  producer; } ;
struct tegra_hsp {int /*<<< orphan*/  lock; int /*<<< orphan*/  shared_irq; int /*<<< orphan*/  mask; } ;
struct mbox_chan {struct tegra_hsp_mailbox* con_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 int EPERM ; 
 scalar_t__ HSP_INT_EMPTY_SHIFT ; 
 int /*<<< orphan*/  HSP_INT_IE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSP_SM_SHRD_MBOX ; 
 int /*<<< orphan*/  HSP_SM_SHRD_MBOX_FULL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tegra_hsp_channel_writel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_hsp_writel (struct tegra_hsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_hsp_mailbox_send_data(struct mbox_chan *chan, void *data)
{
	struct tegra_hsp_mailbox *mb = chan->con_priv;
	struct tegra_hsp *hsp = mb->channel.hsp;
	unsigned long flags;
	u32 value;

	if (WARN_ON(!mb->producer))
		return -EPERM;

	/* copy data and mark mailbox full */
	value = (u32)(unsigned long)data;
	value |= HSP_SM_SHRD_MBOX_FULL;

	tegra_hsp_channel_writel(&mb->channel, value, HSP_SM_SHRD_MBOX);

	/* enable EMPTY interrupt for the shared mailbox */
	spin_lock_irqsave(&hsp->lock, flags);

	hsp->mask |= BIT(HSP_INT_EMPTY_SHIFT + mb->index);
	tegra_hsp_writel(hsp, hsp->mask, HSP_INT_IE(hsp->shared_irq));

	spin_unlock_irqrestore(&hsp->lock, flags);

	return 0;
}