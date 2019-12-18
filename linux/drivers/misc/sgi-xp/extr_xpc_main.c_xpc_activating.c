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
typedef  short u64 ;
struct xpc_partition {scalar_t__ act_state; scalar_t__ reason; int /*<<< orphan*/  act_lock; scalar_t__ remote_rp_pa; } ;
struct TYPE_2__ {scalar_t__ (* make_first_contact ) (struct xpc_partition*) ;int /*<<< orphan*/  (* request_partition_reactivation ) (struct xpc_partition*) ;int /*<<< orphan*/  (* disallow_hb ) (short) ;int /*<<< orphan*/  (* allow_hb ) (short) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 scalar_t__ XPC_P_AS_ACTIVATING ; 
 scalar_t__ XPC_P_AS_ACTIVATION_REQ ; 
 scalar_t__ XPC_P_AS_DEACTIVATING ; 
 scalar_t__ XPC_P_AS_INACTIVE ; 
 int /*<<< orphan*/  XPC_SET_REASON (struct xpc_partition*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,short) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (short) ; 
 scalar_t__ stub2 (struct xpc_partition*) ; 
 int /*<<< orphan*/  stub3 (short) ; 
 int /*<<< orphan*/  stub4 (struct xpc_partition*) ; 
 scalar_t__ xpReactivating ; 
 scalar_t__ xpSuccess ; 
 short xp_max_npartitions ; 
 TYPE_1__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_channel_mgr (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpc_mark_partition_active (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpc_mark_partition_inactive (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpc_part ; 
 int /*<<< orphan*/  xpc_part_deref (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpc_part_ref (struct xpc_partition*) ; 
 struct xpc_partition* xpc_partitions ; 
 scalar_t__ xpc_setup_ch_structures (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpc_teardown_ch_structures (struct xpc_partition*) ; 

__attribute__((used)) static int
xpc_activating(void *__partid)
{
	short partid = (u64)__partid;
	struct xpc_partition *part = &xpc_partitions[partid];
	unsigned long irq_flags;

	DBUG_ON(partid < 0 || partid >= xp_max_npartitions);

	spin_lock_irqsave(&part->act_lock, irq_flags);

	if (part->act_state == XPC_P_AS_DEACTIVATING) {
		part->act_state = XPC_P_AS_INACTIVE;
		spin_unlock_irqrestore(&part->act_lock, irq_flags);
		part->remote_rp_pa = 0;
		return 0;
	}

	/* indicate the thread is activating */
	DBUG_ON(part->act_state != XPC_P_AS_ACTIVATION_REQ);
	part->act_state = XPC_P_AS_ACTIVATING;

	XPC_SET_REASON(part, 0, 0);
	spin_unlock_irqrestore(&part->act_lock, irq_flags);

	dev_dbg(xpc_part, "activating partition %d\n", partid);

	xpc_arch_ops.allow_hb(partid);

	if (xpc_setup_ch_structures(part) == xpSuccess) {
		(void)xpc_part_ref(part);	/* this will always succeed */

		if (xpc_arch_ops.make_first_contact(part) == xpSuccess) {
			xpc_mark_partition_active(part);
			xpc_channel_mgr(part);
			/* won't return until partition is deactivating */
		}

		xpc_part_deref(part);
		xpc_teardown_ch_structures(part);
	}

	xpc_arch_ops.disallow_hb(partid);
	xpc_mark_partition_inactive(part);

	if (part->reason == xpReactivating) {
		/* interrupting ourselves results in activating partition */
		xpc_arch_ops.request_partition_reactivation(part);
	}

	return 0;
}