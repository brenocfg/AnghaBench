#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct tegra_hsp_channel {int dummy; } ;
struct tegra_hsp_mailbox {struct tegra_hsp_channel channel; } ;
struct mbox_chan {struct tegra_hsp_mailbox* con_priv; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  HSP_SM_SHRD_MBOX ; 
 int HSP_SM_SHRD_MBOX_FULL ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mbox_chan_txdone (struct mbox_chan*,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int tegra_hsp_channel_readl (struct tegra_hsp_channel*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tegra_hsp_mailbox_flush(struct mbox_chan *chan,
				   unsigned long timeout)
{
	struct tegra_hsp_mailbox *mb = chan->con_priv;
	struct tegra_hsp_channel *ch = &mb->channel;
	u32 value;

	timeout = jiffies + msecs_to_jiffies(timeout);

	while (time_before(jiffies, timeout)) {
		value = tegra_hsp_channel_readl(ch, HSP_SM_SHRD_MBOX);
		if ((value & HSP_SM_SHRD_MBOX_FULL) == 0) {
			mbox_chan_txdone(chan, 0);
			return 0;
		}

		udelay(1);
	}

	return -ETIME;
}