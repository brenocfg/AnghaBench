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
struct slim_msg_txn {int /*<<< orphan*/  tid; } ;
struct slim_controller {int /*<<< orphan*/  txn_lock; int /*<<< orphan*/  tid_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void slim_free_txn_tid(struct slim_controller *ctrl, struct slim_msg_txn *txn)
{
	unsigned long flags;

	spin_lock_irqsave(&ctrl->txn_lock, flags);
	idr_remove(&ctrl->tid_idr, txn->tid);
	spin_unlock_irqrestore(&ctrl->txn_lock, flags);
}