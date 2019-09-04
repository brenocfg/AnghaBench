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
struct hw_perf_event_extra {size_t idx; scalar_t__ alloc; } ;
struct er_account {int /*<<< orphan*/  ref; } ;
struct cpu_hw_events {TYPE_1__* shared_regs; scalar_t__ is_fake; } ;
struct TYPE_2__ {struct er_account* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__intel_shared_reg_put_constraints(struct cpu_hw_events *cpuc,
				   struct hw_perf_event_extra *reg)
{
	struct er_account *era;

	/*
	 * Only put constraint if extra reg was actually allocated. Also takes
	 * care of event which do not use an extra shared reg.
	 *
	 * Also, if this is a fake cpuc we shouldn't touch any event state
	 * (reg->alloc) and we don't care about leaving inconsistent cpuc state
	 * either since it'll be thrown out.
	 */
	if (!reg->alloc || cpuc->is_fake)
		return;

	era = &cpuc->shared_regs->regs[reg->idx];

	/* one fewer user */
	atomic_dec(&era->ref);

	/* allocate again next time */
	reg->alloc = 0;
}