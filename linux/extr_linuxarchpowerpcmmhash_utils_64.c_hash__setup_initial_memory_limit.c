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
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  early_cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memblock_set_current_limit (scalar_t__) ; 
 scalar_t__ min_t (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ ppc64_rma_size ; 
 int /*<<< orphan*/  u64 ; 

void hash__setup_initial_memory_limit(phys_addr_t first_memblock_base,
				phys_addr_t first_memblock_size)
{
	/* We don't currently support the first MEMBLOCK not mapping 0
	 * physical on those processors
	 */
	BUG_ON(first_memblock_base != 0);

	/*
	 * On virtualized systems the first entry is our RMA region aka VRMA,
	 * non-virtualized 64-bit hash MMU systems don't have a limitation
	 * on real mode access.
	 *
	 * For guests on platforms before POWER9, we clamp the it limit to 1G
	 * to avoid some funky things such as RTAS bugs etc...
	 */
	if (!early_cpu_has_feature(CPU_FTR_HVMODE)) {
		ppc64_rma_size = first_memblock_size;
		if (!early_cpu_has_feature(CPU_FTR_ARCH_300))
			ppc64_rma_size = min_t(u64, ppc64_rma_size, 0x40000000);

		/* Finally limit subsequent allocations */
		memblock_set_current_limit(ppc64_rma_size);
	} else {
		ppc64_rma_size = ULONG_MAX;
	}
}