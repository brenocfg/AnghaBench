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
struct psp_context {int dummy; } ;
struct TYPE_2__ {scalar_t__ load_type; } ;
struct amdgpu_device {TYPE_1__ firmware; struct psp_context psp; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  PSP_RING_TYPE__KM ; 
 int psp_ring_stop (struct psp_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int psp_suspend(void *handle)
{
	int ret;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct psp_context *psp = &adev->psp;

	if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP)
		return 0;

	ret = psp_ring_stop(psp, PSP_RING_TYPE__KM);
	if (ret) {
		DRM_ERROR("PSP ring stop failed\n");
		return ret;
	}

	return 0;
}