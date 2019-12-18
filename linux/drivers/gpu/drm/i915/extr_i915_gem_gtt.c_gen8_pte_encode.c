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
typedef  int gen8_pte_t ;
typedef  enum i915_cache_level { ____Placeholder_i915_cache_level } i915_cache_level ;
typedef  int dma_addr_t ;

/* Variables and functions */
#define  I915_CACHE_NONE 129 
#define  I915_CACHE_WT 128 
 int PPAT_CACHED ; 
 int PPAT_DISPLAY_ELLC ; 
 int PPAT_UNCACHED ; 
 int PTE_READ_ONLY ; 
 int _PAGE_PRESENT ; 
 int _PAGE_RW ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u64 gen8_pte_encode(dma_addr_t addr,
			   enum i915_cache_level level,
			   u32 flags)
{
	gen8_pte_t pte = addr | _PAGE_PRESENT | _PAGE_RW;

	if (unlikely(flags & PTE_READ_ONLY))
		pte &= ~_PAGE_RW;

	switch (level) {
	case I915_CACHE_NONE:
		pte |= PPAT_UNCACHED;
		break;
	case I915_CACHE_WT:
		pte |= PPAT_DISPLAY_ELLC;
		break;
	default:
		pte |= PPAT_CACHED;
		break;
	}

	return pte;
}