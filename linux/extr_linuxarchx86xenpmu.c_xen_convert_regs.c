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
typedef  int uint64_t ;
struct xen_pmu_regs {int cs; scalar_t__ cpl; int /*<<< orphan*/  sp; int /*<<< orphan*/  ip; } ;
struct pt_regs {int cs; int /*<<< orphan*/  sp; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int PMU_SAMPLE_PV ; 
 int PMU_SAMPLE_USER ; 

__attribute__((used)) static void xen_convert_regs(const struct xen_pmu_regs *xen_regs,
			     struct pt_regs *regs, uint64_t pmu_flags)
{
	regs->ip = xen_regs->ip;
	regs->cs = xen_regs->cs;
	regs->sp = xen_regs->sp;

	if (pmu_flags & PMU_SAMPLE_PV) {
		if (pmu_flags & PMU_SAMPLE_USER)
			regs->cs |= 3;
		else
			regs->cs &= ~3;
	} else {
		if (xen_regs->cpl)
			regs->cs |= 3;
		else
			regs->cs &= ~3;
	}
}