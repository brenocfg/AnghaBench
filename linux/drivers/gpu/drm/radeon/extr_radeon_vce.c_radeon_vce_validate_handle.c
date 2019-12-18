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
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_cs_parser {scalar_t__ filp; TYPE_2__* rdev; } ;
struct TYPE_3__ {scalar_t__* filp; scalar_t__* img_size; int /*<<< orphan*/ * handles; } ;
struct TYPE_4__ {TYPE_1__ vce; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 unsigned int RADEON_MAX_VCE_HANDLES ; 
 int /*<<< orphan*/  atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int radeon_vce_validate_handle(struct radeon_cs_parser *p,
				      uint32_t handle, bool *allocated)
{
	unsigned i;

	*allocated = false;

	/* validate the handle */
	for (i = 0; i < RADEON_MAX_VCE_HANDLES; ++i) {
		if (atomic_read(&p->rdev->vce.handles[i]) == handle) {
			if (p->rdev->vce.filp[i] != p->filp) {
				DRM_ERROR("VCE handle collision detected!\n");
				return -EINVAL;
			}
			return i;
		}
	}

	/* handle not found try to alloc a new one */
	for (i = 0; i < RADEON_MAX_VCE_HANDLES; ++i) {
		if (!atomic_cmpxchg(&p->rdev->vce.handles[i], 0, handle)) {
			p->rdev->vce.filp[i] = p->filp;
			p->rdev->vce.img_size[i] = 0;
			*allocated = true;
			return i;
		}
	}

	DRM_ERROR("No more free VCE handles!\n");
	return -EINVAL;
}