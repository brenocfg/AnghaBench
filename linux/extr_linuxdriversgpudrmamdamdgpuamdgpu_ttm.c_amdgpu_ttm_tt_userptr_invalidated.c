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
struct ttm_tt {int dummy; } ;
struct amdgpu_ttm_tt {int /*<<< orphan*/  mmu_invalidations; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 

bool amdgpu_ttm_tt_userptr_invalidated(struct ttm_tt *ttm,
				       int *last_invalidated)
{
	struct amdgpu_ttm_tt *gtt = (void *)ttm;
	int prev_invalidated = *last_invalidated;

	*last_invalidated = atomic_read(&gtt->mmu_invalidations);
	return prev_invalidated != *last_invalidated;
}