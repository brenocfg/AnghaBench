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
struct xpc_partition {int dummy; } ;
struct xpc_channel {size_t partid; int /*<<< orphan*/  lock; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_DEACTIVATE_PARTITION (struct xpc_partition*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int xpSuccess ; 
 struct xpc_partition* xpc_partitions ; 
 int xpc_send_activate_IRQ_uv (struct xpc_partition*,void*,size_t,int) ; 

__attribute__((used)) static void
xpc_send_activate_IRQ_ch_uv(struct xpc_channel *ch, unsigned long *irq_flags,
			 void *msg, size_t msg_size, int msg_type)
{
	struct xpc_partition *part = &xpc_partitions[ch->partid];
	enum xp_retval ret;

	ret = xpc_send_activate_IRQ_uv(part, msg, msg_size, msg_type);
	if (unlikely(ret != xpSuccess)) {
		if (irq_flags != NULL)
			spin_unlock_irqrestore(&ch->lock, *irq_flags);

		XPC_DEACTIVATE_PARTITION(part, ret);

		if (irq_flags != NULL)
			spin_lock_irqsave(&ch->lock, *irq_flags);
	}
}