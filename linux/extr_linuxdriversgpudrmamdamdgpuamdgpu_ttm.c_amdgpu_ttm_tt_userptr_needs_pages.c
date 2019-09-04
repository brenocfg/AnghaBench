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
struct amdgpu_ttm_tt {scalar_t__ last_set_pages; int /*<<< orphan*/  mmu_invalidations; int /*<<< orphan*/  userptr; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

bool amdgpu_ttm_tt_userptr_needs_pages(struct ttm_tt *ttm)
{
	struct amdgpu_ttm_tt *gtt = (void *)ttm;

	if (gtt == NULL || !gtt->userptr)
		return false;

	return atomic_read(&gtt->mmu_invalidations) != gtt->last_set_pages;
}