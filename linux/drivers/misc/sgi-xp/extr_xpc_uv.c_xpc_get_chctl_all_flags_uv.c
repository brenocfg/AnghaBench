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
union xpc_channel_ctl_flags {scalar_t__ all_flags; } ;
typedef  scalar_t__ u64 ;
struct xpc_partition {int /*<<< orphan*/  chctl_lock; union xpc_channel_ctl_flags chctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u64
xpc_get_chctl_all_flags_uv(struct xpc_partition *part)
{
	unsigned long irq_flags;
	union xpc_channel_ctl_flags chctl;

	spin_lock_irqsave(&part->chctl_lock, irq_flags);
	chctl = part->chctl;
	if (chctl.all_flags != 0)
		part->chctl.all_flags = 0;

	spin_unlock_irqrestore(&part->chctl_lock, irq_flags);
	return chctl.all_flags;
}