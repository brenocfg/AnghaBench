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
struct TYPE_3__ {int /*<<< orphan*/  ring; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/ * ring_obj; int /*<<< orphan*/  ring_size; } ;
struct TYPE_4__ {TYPE_1__ ih; } ;
struct amdgpu_device {TYPE_2__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GTT ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static int amdgpu_ih_ring_alloc(struct amdgpu_device *adev)
{
	int r;

	/* Allocate ring buffer */
	if (adev->irq.ih.ring_obj == NULL) {
		r = amdgpu_bo_create_kernel(adev, adev->irq.ih.ring_size,
					    PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
					    &adev->irq.ih.ring_obj,
					    &adev->irq.ih.gpu_addr,
					    (void **)&adev->irq.ih.ring);
		if (r) {
			DRM_ERROR("amdgpu: failed to create ih ring buffer (%d).\n", r);
			return r;
		}
	}
	return 0;
}