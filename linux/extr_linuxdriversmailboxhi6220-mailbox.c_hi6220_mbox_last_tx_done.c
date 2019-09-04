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
struct mbox_chan {struct hi6220_mbox_chan* con_priv; } ;
struct hi6220_mbox_chan {int /*<<< orphan*/  slot; struct hi6220_mbox* parent; } ;
struct hi6220_mbox {scalar_t__ base; int /*<<< orphan*/  tx_irq_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ MBOX_MODE_REG (int /*<<< orphan*/ ) ; 
 int MBOX_STATE_IDLE ; 
 int MBOX_STATE_MASK ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static bool hi6220_mbox_last_tx_done(struct mbox_chan *chan)
{
	struct hi6220_mbox_chan *mchan = chan->con_priv;
	struct hi6220_mbox *mbox = mchan->parent;
	u32 state;

	/* Only set idle state for polling mode */
	BUG_ON(mbox->tx_irq_mode);

	state = readl(mbox->base + MBOX_MODE_REG(mchan->slot));
	return ((state & MBOX_STATE_MASK) == MBOX_STATE_IDLE);
}