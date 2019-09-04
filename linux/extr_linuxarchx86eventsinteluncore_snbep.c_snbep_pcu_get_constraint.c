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
typedef  int u64 ;
struct hw_perf_event_extra {int idx; int config; int alloc; } ;
struct TYPE_2__ {struct hw_perf_event_extra extra_reg; } ;
struct perf_event {TYPE_1__ hw; } ;
struct intel_uncore_extra_reg {int config; int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; } ;
struct intel_uncore_box {struct intel_uncore_extra_reg* shared_regs; } ;
struct event_constraint {int dummy; } ;

/* Variables and functions */
 int EXTRA_REG_NONE ; 
 int /*<<< orphan*/  __BITS_VALUE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int snbep_pcu_alter_er (struct perf_event*,int,int) ; 
 int /*<<< orphan*/  uncore_box_is_fake (struct intel_uncore_box*) ; 
 struct event_constraint uncore_constraint_empty ; 

__attribute__((used)) static struct event_constraint *
snbep_pcu_get_constraint(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	struct intel_uncore_extra_reg *er = &box->shared_regs[0];
	unsigned long flags;
	int idx = reg1->idx;
	u64 mask, config1 = reg1->config;
	bool ok = false;

	if (reg1->idx == EXTRA_REG_NONE ||
	    (!uncore_box_is_fake(box) && reg1->alloc))
		return NULL;
again:
	mask = 0xffULL << (idx * 8);
	raw_spin_lock_irqsave(&er->lock, flags);
	if (!__BITS_VALUE(atomic_read(&er->ref), idx, 8) ||
	    !((config1 ^ er->config) & mask)) {
		atomic_add(1 << (idx * 8), &er->ref);
		er->config &= ~mask;
		er->config |= config1 & mask;
		ok = true;
	}
	raw_spin_unlock_irqrestore(&er->lock, flags);

	if (!ok) {
		idx = (idx + 1) % 4;
		if (idx != reg1->idx) {
			config1 = snbep_pcu_alter_er(event, idx, false);
			goto again;
		}
		return &uncore_constraint_empty;
	}

	if (!uncore_box_is_fake(box)) {
		if (idx != reg1->idx)
			snbep_pcu_alter_er(event, idx, true);
		reg1->alloc = 1;
	}
	return NULL;
}