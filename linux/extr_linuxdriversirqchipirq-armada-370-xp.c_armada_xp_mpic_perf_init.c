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

/* Variables and functions */
 int /*<<< orphan*/  ARMADA_370_XP_INT_CAUSE_PERF (unsigned long) ; 
 scalar_t__ ARMADA_370_XP_INT_FABRIC_MASK_OFFS ; 
 unsigned long cpu_logical_map (int /*<<< orphan*/ ) ; 
 scalar_t__ per_cpu_int_base ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void armada_xp_mpic_perf_init(void)
{
	unsigned long cpuid = cpu_logical_map(smp_processor_id());

	/* Enable Performance Counter Overflow interrupts */
	writel(ARMADA_370_XP_INT_CAUSE_PERF(cpuid),
	       per_cpu_int_base + ARMADA_370_XP_INT_FABRIC_MASK_OFFS);
}