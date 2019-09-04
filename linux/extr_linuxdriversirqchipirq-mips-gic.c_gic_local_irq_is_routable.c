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
typedef  int u32 ;

/* Variables and functions */
#define  GIC_LOCAL_INT_FDC 132 
#define  GIC_LOCAL_INT_PERFCTR 131 
#define  GIC_LOCAL_INT_SWINT0 130 
#define  GIC_LOCAL_INT_SWINT1 129 
#define  GIC_LOCAL_INT_TIMER 128 
 int GIC_VX_CTL_FDC_ROUTABLE ; 
 int GIC_VX_CTL_PERFCNT_ROUTABLE ; 
 int GIC_VX_CTL_SWINT_ROUTABLE ; 
 int GIC_VX_CTL_TIMER_ROUTABLE ; 
 scalar_t__ cpu_has_veic ; 
 int read_gic_vl_ctl () ; 

__attribute__((used)) static bool gic_local_irq_is_routable(int intr)
{
	u32 vpe_ctl;

	/* All local interrupts are routable in EIC mode. */
	if (cpu_has_veic)
		return true;

	vpe_ctl = read_gic_vl_ctl();
	switch (intr) {
	case GIC_LOCAL_INT_TIMER:
		return vpe_ctl & GIC_VX_CTL_TIMER_ROUTABLE;
	case GIC_LOCAL_INT_PERFCTR:
		return vpe_ctl & GIC_VX_CTL_PERFCNT_ROUTABLE;
	case GIC_LOCAL_INT_FDC:
		return vpe_ctl & GIC_VX_CTL_FDC_ROUTABLE;
	case GIC_LOCAL_INT_SWINT0:
	case GIC_LOCAL_INT_SWINT1:
		return vpe_ctl & GIC_VX_CTL_SWINT_ROUTABLE;
	default:
		return true;
	}
}