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
typedef  scalar_t__ u64 ;
struct xpc_partition {scalar_t__ act_state; int /*<<< orphan*/  act_lock; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 short XPC_PARTID (struct xpc_partition*) ; 
 scalar_t__ XPC_P_AS_ACTIVATION_REQ ; 
 scalar_t__ XPC_P_AS_INACTIVE ; 
 int /*<<< orphan*/  XPC_SET_REASON (struct xpc_partition*,int /*<<< orphan*/ ,int) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,void*,char*,short) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xpCloneKThread ; 
 int /*<<< orphan*/  xpCloneKThreadFailed ; 
 int /*<<< orphan*/  xpc_activating ; 

void
xpc_activate_partition(struct xpc_partition *part)
{
	short partid = XPC_PARTID(part);
	unsigned long irq_flags;
	struct task_struct *kthread;

	spin_lock_irqsave(&part->act_lock, irq_flags);

	DBUG_ON(part->act_state != XPC_P_AS_INACTIVE);

	part->act_state = XPC_P_AS_ACTIVATION_REQ;
	XPC_SET_REASON(part, xpCloneKThread, __LINE__);

	spin_unlock_irqrestore(&part->act_lock, irq_flags);

	kthread = kthread_run(xpc_activating, (void *)((u64)partid), "xpc%02d",
			      partid);
	if (IS_ERR(kthread)) {
		spin_lock_irqsave(&part->act_lock, irq_flags);
		part->act_state = XPC_P_AS_INACTIVE;
		XPC_SET_REASON(part, xpCloneKThreadFailed, __LINE__);
		spin_unlock_irqrestore(&part->act_lock, irq_flags);
	}
}