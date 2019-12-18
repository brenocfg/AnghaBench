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
typedef  int u64 ;
typedef  int u32 ;
typedef  enum qm_memory { ____Placeholder_qm_memory } qm_memory ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MEMREMAP_WB ; 
 int PFDR_AR_EN ; 
 int REG_FQD_BARE ; 
 int REG_PFDR_BARE ; 
 int REG_offset_AR ; 
 int REG_offset_BAR ; 
 int __qman_requires_cleanup ; 
 int /*<<< orphan*/  flush_dcache_range (unsigned long,int) ; 
 int ilog2 (int) ; 
 scalar_t__ is_power_of_2 (int) ; 
 int lower_32_bits (int) ; 
 void* memremap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memunmap (void*) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int) ; 
 int qm_ccsr_in (int) ; 
 int /*<<< orphan*/  qm_ccsr_out (int,int) ; 
 int qm_memory_fqd ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int qm_set_memory(enum qm_memory memory, u64 ba, u32 size)
{
	void *ptr;
	u32 offset = (memory == qm_memory_fqd) ? REG_FQD_BARE : REG_PFDR_BARE;
	u32 exp = ilog2(size);
	u32 bar, bare;

	/* choke if size isn't within range */
	DPAA_ASSERT((size >= 4096) && (size <= 1024*1024*1024) &&
		    is_power_of_2(size));
	/* choke if 'ba' has lower-alignment than 'size' */
	DPAA_ASSERT(!(ba & (size - 1)));

	/* Check to see if QMan has already been initialized */
	bar = qm_ccsr_in(offset + REG_offset_BAR);
	if (bar) {
		/* Maker sure ba == what was programmed) */
		bare = qm_ccsr_in(offset);
		if (bare != upper_32_bits(ba) || bar != lower_32_bits(ba)) {
			pr_err("Attempted to reinitialize QMan with different BAR, got 0x%llx read BARE=0x%x BAR=0x%x\n",
			       ba, bare, bar);
			return -ENOMEM;
		}
		__qman_requires_cleanup = 1;
		/* Return 1 to indicate memory was previously programmed */
		return 1;
	}
	/* Need to temporarily map the area to make sure it is zeroed */
	ptr = memremap(ba, size, MEMREMAP_WB);
	if (!ptr) {
		pr_crit("memremap() of QMan private memory failed\n");
		return -ENOMEM;
	}
	memset(ptr, 0, size);

#ifdef CONFIG_PPC
	/*
	 * PPC doesn't appear to flush the cache on memunmap() but the
	 * cache must be flushed since QMan does non coherent accesses
	 * to this memory
	 */
	flush_dcache_range((unsigned long) ptr, (unsigned long) ptr+size);
#endif
	memunmap(ptr);

	qm_ccsr_out(offset, upper_32_bits(ba));
	qm_ccsr_out(offset + REG_offset_BAR, lower_32_bits(ba));
	qm_ccsr_out(offset + REG_offset_AR, PFDR_AR_EN | (exp - 1));
	return 0;
}