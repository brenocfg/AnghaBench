#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct ttm_tt {int dummy; } ;
struct ttm_mem_reg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gart_pte_flags; } ;
struct amdgpu_device {TYPE_1__ gart; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_PTE_READABLE ; 
 int /*<<< orphan*/  AMDGPU_PTE_WRITEABLE ; 
 int /*<<< orphan*/  amdgpu_ttm_tt_is_readonly (struct ttm_tt*) ; 
 int /*<<< orphan*/  amdgpu_ttm_tt_pde_flags (struct ttm_tt*,struct ttm_mem_reg*) ; 

uint64_t amdgpu_ttm_tt_pte_flags(struct amdgpu_device *adev, struct ttm_tt *ttm,
				 struct ttm_mem_reg *mem)
{
	uint64_t flags = amdgpu_ttm_tt_pde_flags(ttm, mem);

	flags |= adev->gart.gart_pte_flags;
	flags |= AMDGPU_PTE_READABLE;

	if (!amdgpu_ttm_tt_is_readonly(ttm))
		flags |= AMDGPU_PTE_WRITEABLE;

	return flags;
}