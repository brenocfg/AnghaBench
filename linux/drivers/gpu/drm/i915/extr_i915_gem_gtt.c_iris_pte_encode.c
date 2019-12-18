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
 int /*<<< orphan*/  GEN6_PTE_VALID ; 
 int /*<<< orphan*/  HSW_PTE_ADDR_ENCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSW_WB_ELLC_LLC_AGE3 ; 
 int /*<<< orphan*/  HSW_WT_ELLC_LLC_AGE3 ; 
#define  I915_CACHE_NONE 129 
#define  I915_CACHE_WT 128 

__attribute__((used)) static u64 iris_pte_encode(dma_addr_t addr,
			   enum i915_cache_level level,
			   u32 flags)
{
	gen6_pte_t pte = GEN6_PTE_VALID;
	pte |= HSW_PTE_ADDR_ENCODE(addr);

	switch (level) {
	case I915_CACHE_NONE:
		break;
	case I915_CACHE_WT:
		pte |= HSW_WT_ELLC_LLC_AGE3;
		break;
	default:
		pte |= HSW_WB_ELLC_LLC_AGE3;
		break;
	}

	return pte;
}