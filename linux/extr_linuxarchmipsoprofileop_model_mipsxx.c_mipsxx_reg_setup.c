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
struct op_counter_config {scalar_t__ count; scalar_t__ exl; scalar_t__ user; scalar_t__ kernel; int /*<<< orphan*/  event; int /*<<< orphan*/  enabled; } ;
struct TYPE_4__ {unsigned int num_counters; } ;
struct TYPE_3__ {int* control; scalar_t__* counter; } ;

/* Variables and functions */
 scalar_t__ CPU_XLR ; 
 int MIPS_PERFCTRL_EXL ; 
 int MIPS_PERFCTRL_IE ; 
 int MIPS_PERFCTRL_K ; 
 int MIPS_PERFCTRL_U ; 
 int M_PERFCTL_EVENT (int /*<<< orphan*/ ) ; 
 int XLR_PERFCTRL_ALLTHREADS ; 
 scalar_t__ boot_cpu_type () ; 
 TYPE_2__ op_model_mipsxx_ops ; 
 TYPE_1__ reg ; 

__attribute__((used)) static void mipsxx_reg_setup(struct op_counter_config *ctr)
{
	unsigned int counters = op_model_mipsxx_ops.num_counters;
	int i;

	/* Compute the performance counter control word.  */
	for (i = 0; i < counters; i++) {
		reg.control[i] = 0;
		reg.counter[i] = 0;

		if (!ctr[i].enabled)
			continue;

		reg.control[i] = M_PERFCTL_EVENT(ctr[i].event) |
				 MIPS_PERFCTRL_IE;
		if (ctr[i].kernel)
			reg.control[i] |= MIPS_PERFCTRL_K;
		if (ctr[i].user)
			reg.control[i] |= MIPS_PERFCTRL_U;
		if (ctr[i].exl)
			reg.control[i] |= MIPS_PERFCTRL_EXL;
		if (boot_cpu_type() == CPU_XLR)
			reg.control[i] |= XLR_PERFCTRL_ALLTHREADS;
		reg.counter[i] = 0x80000000 - ctr[i].count;
	}
}