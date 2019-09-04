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
struct amdgpu_sa_manager {int /*<<< orphan*/ * flist; } ;

/* Variables and functions */
 int AMDGPU_SA_NUM_FENCE_LISTS ; 
 unsigned int amdgpu_sa_bo_hole_eoffset (struct amdgpu_sa_manager*) ; 
 unsigned int amdgpu_sa_bo_hole_soffset (struct amdgpu_sa_manager*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool amdgpu_sa_event(struct amdgpu_sa_manager *sa_manager,
			    unsigned size, unsigned align)
{
	unsigned soffset, eoffset, wasted;
	int i;

	for (i = 0; i < AMDGPU_SA_NUM_FENCE_LISTS; ++i)
		if (!list_empty(&sa_manager->flist[i]))
			return true;

	soffset = amdgpu_sa_bo_hole_soffset(sa_manager);
	eoffset = amdgpu_sa_bo_hole_eoffset(sa_manager);
	wasted = (align - (soffset % align)) % align;

	if ((eoffset - soffset) >= (size + wasted)) {
		return true;
	}

	return false;
}