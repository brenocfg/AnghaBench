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
struct TYPE_3__ {int fcr31; } ;
struct TYPE_4__ {TYPE_1__ fpu; } ;
struct task_struct {TYPE_2__ thread; } ;
struct cpuinfo_mips {int fpu_csr31; int fpu_msk31; } ;
struct arch_elf_state {int nan_2008; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int FPU_CSR_ABS2008 ; 
 int FPU_CSR_NAN2008 ; 
 struct cpuinfo_mips boot_cpu_data ; 
 struct task_struct* current ; 

void mips_set_personality_nan(struct arch_elf_state *state)
{
	struct cpuinfo_mips *c = &boot_cpu_data;
	struct task_struct *t = current;

	t->thread.fpu.fcr31 = c->fpu_csr31;
	switch (state->nan_2008) {
	case 0:
		break;
	case 1:
		if (!(c->fpu_msk31 & FPU_CSR_NAN2008))
			t->thread.fpu.fcr31 |= FPU_CSR_NAN2008;
		if (!(c->fpu_msk31 & FPU_CSR_ABS2008))
			t->thread.fpu.fcr31 |= FPU_CSR_ABS2008;
		break;
	default:
		BUG();
	}
}