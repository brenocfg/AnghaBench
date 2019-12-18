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
typedef  int /*<<< orphan*/  uint64_t ;
struct ttm_tt {scalar_t__ caching_state; } ;
struct ttm_mem_reg {scalar_t__ mem_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_PTE_SNOOPED ; 
 int /*<<< orphan*/  AMDGPU_PTE_SYSTEM ; 
 int /*<<< orphan*/  AMDGPU_PTE_VALID ; 
 scalar_t__ TTM_PL_SYSTEM ; 
 scalar_t__ TTM_PL_TT ; 
 scalar_t__ tt_cached ; 

uint64_t amdgpu_ttm_tt_pde_flags(struct ttm_tt *ttm, struct ttm_mem_reg *mem)
{
	uint64_t flags = 0;

	if (mem && mem->mem_type != TTM_PL_SYSTEM)
		flags |= AMDGPU_PTE_VALID;

	if (mem && mem->mem_type == TTM_PL_TT) {
		flags |= AMDGPU_PTE_SYSTEM;

		if (ttm->caching_state == tt_cached)
			flags |= AMDGPU_PTE_SNOOPED;
	}

	return flags;
}