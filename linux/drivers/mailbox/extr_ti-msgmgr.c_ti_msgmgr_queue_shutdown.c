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
struct ti_queue_inst {int /*<<< orphan*/  rx_buff; int /*<<< orphan*/  irq; int /*<<< orphan*/  is_tx; } ;
struct mbox_chan {struct ti_queue_inst* con_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mbox_chan*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_msgmgr_queue_shutdown(struct mbox_chan *chan)
{
	struct ti_queue_inst *qinst = chan->con_priv;

	if (!qinst->is_tx) {
		free_irq(qinst->irq, chan);
		kfree(qinst->rx_buff);
	}
}