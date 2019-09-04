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
struct task_struct {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void setup_ksp_vsid(struct task_struct *p, unsigned long sp)
{
#ifdef CONFIG_PPC_BOOK3S_64
	unsigned long sp_vsid;
	unsigned long llp = mmu_psize_defs[mmu_linear_psize].sllp;

	if (radix_enabled())
		return;

	if (mmu_has_feature(MMU_FTR_1T_SEGMENT))
		sp_vsid = get_kernel_vsid(sp, MMU_SEGSIZE_1T)
			<< SLB_VSID_SHIFT_1T;
	else
		sp_vsid = get_kernel_vsid(sp, MMU_SEGSIZE_256M)
			<< SLB_VSID_SHIFT;
	sp_vsid |= SLB_VSID_KERNEL | llp;
	p->thread.ksp_vsid = sp_vsid;
#endif
}