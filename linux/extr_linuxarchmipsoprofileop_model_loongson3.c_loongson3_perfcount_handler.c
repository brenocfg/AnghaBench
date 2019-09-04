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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int reset_counter1; int reset_counter2; scalar_t__ ctr2_enable; scalar_t__ ctr1_enable; } ;

/* Variables and functions */
 int CAUSEF_PCI ; 
 int CAUSEF_TI ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int LOONGSON3_PERFCNT_OVERFLOW ; 
 struct pt_regs* get_irq_regs () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  oprofile_add_sample (struct pt_regs*,int) ; 
 int read_c0_cause () ; 
 int read_c0_perfhi1 () ; 
 int read_c0_perfhi2 () ; 
 TYPE_1__ reg ; 
 int /*<<< orphan*/  write_c0_perfhi1 (int) ; 
 int /*<<< orphan*/  write_c0_perfhi2 (int) ; 

__attribute__((used)) static int loongson3_perfcount_handler(void)
{
	unsigned long flags;
	uint64_t counter1, counter2;
	uint32_t cause, handled = IRQ_NONE;
	struct pt_regs *regs = get_irq_regs();

	cause = read_c0_cause();
	if (!(cause & CAUSEF_PCI))
		return handled;

	counter1 = read_c0_perfhi1();
	counter2 = read_c0_perfhi2();

	local_irq_save(flags);

	if (counter1 & LOONGSON3_PERFCNT_OVERFLOW) {
		if (reg.ctr1_enable)
			oprofile_add_sample(regs, 0);
		counter1 = reg.reset_counter1;
	}
	if (counter2 & LOONGSON3_PERFCNT_OVERFLOW) {
		if (reg.ctr2_enable)
			oprofile_add_sample(regs, 1);
		counter2 = reg.reset_counter2;
	}

	local_irq_restore(flags);

	write_c0_perfhi1(counter1);
	write_c0_perfhi2(counter2);

	if (!(cause & CAUSEF_TI))
		handled = IRQ_HANDLED;

	return handled;
}