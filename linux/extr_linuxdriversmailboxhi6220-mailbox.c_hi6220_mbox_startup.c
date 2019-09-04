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
struct hi6220_mbox_chan {int /*<<< orphan*/  ack_irq; scalar_t__ dir; struct hi6220_mbox* parent; } ;
struct hi6220_mbox {int /*<<< orphan*/  ipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_INT_ENA_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hi6220_mbox_startup(struct mbox_chan *chan)
{
	struct hi6220_mbox_chan *mchan = chan->con_priv;
	struct hi6220_mbox *mbox = mchan->parent;

	mchan->dir = 0;

	/* enable interrupt */
	writel(BIT(mchan->ack_irq), ACK_INT_ENA_REG(mbox->ipc));
	return 0;
}