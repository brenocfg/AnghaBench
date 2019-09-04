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
union xpc_channel_ctl_flags {int /*<<< orphan*/  all_flags; int /*<<< orphan*/ * flags; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  u8 ;
struct xpc_partition_sn2 {int /*<<< orphan*/  notify_IRQ_phys_cpuid; int /*<<< orphan*/  notify_IRQ_nasid; int /*<<< orphan*/  remote_chctl_amo_va; } ;
struct TYPE_2__ {struct xpc_partition_sn2 sn2; } ;
struct xpc_partition {scalar_t__ act_state; TYPE_1__ sn; } ;
struct xpc_channel {size_t partid; size_t number; int /*<<< orphan*/  lock; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  SGI_XPC_NOTIFY ; 
 int /*<<< orphan*/  XPC_DEACTIVATE_PARTITION (struct xpc_partition*,int) ; 
 scalar_t__ XPC_P_AS_DEACTIVATING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,size_t,size_t,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int xpSuccess ; 
 int /*<<< orphan*/  xpc_chan ; 
 struct xpc_partition* xpc_partitions ; 
 int xpc_send_IRQ_sn2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xpc_send_notify_IRQ_sn2(struct xpc_channel *ch, u8 chctl_flag,
			char *chctl_flag_string, unsigned long *irq_flags)
{
	struct xpc_partition *part = &xpc_partitions[ch->partid];
	struct xpc_partition_sn2 *part_sn2 = &part->sn.sn2;
	union xpc_channel_ctl_flags chctl = { 0 };
	enum xp_retval ret;

	if (likely(part->act_state != XPC_P_AS_DEACTIVATING)) {
		chctl.flags[ch->number] = chctl_flag;
		ret = xpc_send_IRQ_sn2(part_sn2->remote_chctl_amo_va,
				       chctl.all_flags,
				       part_sn2->notify_IRQ_nasid,
				       part_sn2->notify_IRQ_phys_cpuid,
				       SGI_XPC_NOTIFY);
		dev_dbg(xpc_chan, "%s sent to partid=%d, channel=%d, ret=%d\n",
			chctl_flag_string, ch->partid, ch->number, ret);
		if (unlikely(ret != xpSuccess)) {
			if (irq_flags != NULL)
				spin_unlock_irqrestore(&ch->lock, *irq_flags);
			XPC_DEACTIVATE_PARTITION(part, ret);
			if (irq_flags != NULL)
				spin_lock_irqsave(&ch->lock, *irq_flags);
		}
	}
}