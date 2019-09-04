#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int num_counters; } ;
struct TYPE_3__ {int /*<<< orphan*/ * counter; } ;

/* Variables and functions */
 int CAUSEF_PCI ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 unsigned int MIPS_PERFCTRL_IE ; 
 unsigned int M_COUNTER_OVERFLOW ; 
 scalar_t__ cpu_has_mips_r2 ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 TYPE_2__ op_model_mipsxx_ops ; 
 int /*<<< orphan*/  oprofile_add_sample (int /*<<< orphan*/ ,int) ; 
 unsigned int r_c0_perfcntr0 () ; 
 unsigned int r_c0_perfcntr1 () ; 
 unsigned int r_c0_perfcntr2 () ; 
 unsigned int r_c0_perfcntr3 () ; 
 unsigned int r_c0_perfctrl0 () ; 
 unsigned int r_c0_perfctrl1 () ; 
 unsigned int r_c0_perfctrl2 () ; 
 unsigned int r_c0_perfctrl3 () ; 
 int read_c0_cause () ; 
 TYPE_1__ reg ; 
 int /*<<< orphan*/  w_c0_perfcntr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfcntr1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfcntr2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfcntr3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mipsxx_perfcount_handler(void)
{
	unsigned int counters = op_model_mipsxx_ops.num_counters;
	unsigned int control;
	unsigned int counter;
	int handled = IRQ_NONE;

	if (cpu_has_mips_r2 && !(read_c0_cause() & CAUSEF_PCI))
		return handled;

	switch (counters) {
#define HANDLE_COUNTER(n)						\
	case n + 1:							\
		control = r_c0_perfctrl ## n();				\
		counter = r_c0_perfcntr ## n();				\
		if ((control & MIPS_PERFCTRL_IE) &&			\
		    (counter & M_COUNTER_OVERFLOW)) {			\
			oprofile_add_sample(get_irq_regs(), n);		\
			w_c0_perfcntr ## n(reg.counter[n]);		\
			handled = IRQ_HANDLED;				\
		}
	HANDLE_COUNTER(3)
	HANDLE_COUNTER(2)
	HANDLE_COUNTER(1)
	HANDLE_COUNTER(0)
	}

	return handled;
}