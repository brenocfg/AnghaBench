#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct amdgpu_cs_parser {scalar_t__ filp; TYPE_2__* adev; } ;
struct TYPE_3__ {scalar_t__* filp; scalar_t__* img_size; int /*<<< orphan*/ * handles; } ;
struct TYPE_4__ {TYPE_1__ vce; } ;

/* Variables and functions */
 unsigned int AMDGPU_MAX_VCE_HANDLES ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_vce_validate_handle(struct amdgpu_cs_parser *p,
				      uint32_t handle, uint32_t *allocated)
{
	unsigned i;

	/* validate the handle */
	for (i = 0; i < AMDGPU_MAX_VCE_HANDLES; ++i) {
		if (atomic_read(&p->adev->vce.handles[i]) == handle) {
			if (p->adev->vce.filp[i] != p->filp) {
				DRM_ERROR("VCE handle collision detected!\n");
				return -EINVAL;
			}
			return i;
		}
	}

	/* handle not found try to alloc a new one */
	for (i = 0; i < AMDGPU_MAX_VCE_HANDLES; ++i) {
		if (!atomic_cmpxchg(&p->adev->vce.handles[i], 0, handle)) {
			p->adev->vce.filp[i] = p->filp;
			p->adev->vce.img_size[i] = 0;
			*allocated |= 1 << i;
			return i;
		}
	}

	DRM_ERROR("No more free VCE handles!\n");
	return -EINVAL;
}