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
struct mbox_chan {struct hi6220_mbox_chan* con_priv; } ;
struct hi6220_mbox_chan {size_t ack_irq; struct hi6220_mbox* parent; } ;
struct hi6220_mbox {int /*<<< orphan*/ ** irq_map_chan; int /*<<< orphan*/  ipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_INT_DIS_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT (size_t) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hi6220_mbox_shutdown(struct mbox_chan *chan)
{
	struct hi6220_mbox_chan *mchan = chan->con_priv;
	struct hi6220_mbox *mbox = mchan->parent;

	/* disable interrupt */
	writel(BIT(mchan->ack_irq), ACK_INT_DIS_REG(mbox->ipc));
	mbox->irq_map_chan[mchan->ack_irq] = NULL;
}