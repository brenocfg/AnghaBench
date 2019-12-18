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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  gen6_pte_t ;
typedef  enum i915_cache_level { ____Placeholder_i915_cache_level } i915_cache_level ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_PTE_ADDR_ENCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN6_PTE_CACHE_LLC ; 
 int /*<<< orphan*/  GEN6_PTE_UNCACHED ; 
 int /*<<< orphan*/  GEN6_PTE_VALID ; 
 int /*<<< orphan*/  GEN7_PTE_CACHE_L3_LLC ; 
#define  I915_CACHE_L3_LLC 130 
#define  I915_CACHE_LLC 129 
#define  I915_CACHE_NONE 128 
 int /*<<< orphan*/  MISSING_CASE (int) ; 

__attribute__((used)) static u64 ivb_pte_encode(dma_addr_t addr,
			  enum i915_cache_level level,
			  u32 flags)
{
	gen6_pte_t pte = GEN6_PTE_VALID;
	pte |= GEN6_PTE_ADDR_ENCODE(addr);

	switch (level) {
	case I915_CACHE_L3_LLC:
		pte |= GEN7_PTE_CACHE_L3_LLC;
		break;
	case I915_CACHE_LLC:
		pte |= GEN6_PTE_CACHE_LLC;
		break;
	case I915_CACHE_NONE:
		pte |= GEN6_PTE_UNCACHED;
		break;
	default:
		MISSING_CASE(level);
	}

	return pte;
}