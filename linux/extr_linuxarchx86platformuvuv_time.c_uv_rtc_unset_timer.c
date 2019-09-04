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
typedef  scalar_t__ u64 ;
struct uv_rtc_timer_head {int next_cpu; int /*<<< orphan*/  lock; TYPE_1__* cpu; } ;
struct TYPE_2__ {scalar_t__ expires; } ;

/* Variables and functions */
 scalar_t__ ULLONG_MAX ; 
 struct uv_rtc_timer_head** blade_info ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int uv_cpu_blade_processor_id (int) ; 
 int uv_cpu_to_blade_id (int) ; 
 int uv_cpu_to_pnode (int) ; 
 scalar_t__ uv_read_rtc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rtc_find_next_timer (struct uv_rtc_timer_head*,int) ; 

__attribute__((used)) static int uv_rtc_unset_timer(int cpu, int force)
{
	int pnode = uv_cpu_to_pnode(cpu);
	int bid = uv_cpu_to_blade_id(cpu);
	struct uv_rtc_timer_head *head = blade_info[bid];
	int bcpu = uv_cpu_blade_processor_id(cpu);
	u64 *t = &head->cpu[bcpu].expires;
	unsigned long flags;
	int rc = 0;

	spin_lock_irqsave(&head->lock, flags);

	if ((head->next_cpu == bcpu && uv_read_rtc(NULL) >= *t) || force)
		rc = 1;

	if (rc) {
		*t = ULLONG_MAX;
		/* Was the hardware setup for this timer? */
		if (head->next_cpu == bcpu)
			uv_rtc_find_next_timer(head, pnode);
	}

	spin_unlock_irqrestore(&head->lock, flags);

	return rc;
}