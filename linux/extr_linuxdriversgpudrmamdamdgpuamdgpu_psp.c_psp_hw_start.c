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
struct psp_context {struct amdgpu_device* adev; } ;
struct amdgpu_device {int /*<<< orphan*/  in_gpu_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSP_RING_TYPE__KM ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int psp_asd_load (struct psp_context*) ; 
 int psp_bootloader_load_sos (struct psp_context*) ; 
 int psp_bootloader_load_sysdrv (struct psp_context*) ; 
 int psp_ring_create (struct psp_context*,int /*<<< orphan*/ ) ; 
 int psp_tmr_load (struct psp_context*) ; 

__attribute__((used)) static int psp_hw_start(struct psp_context *psp)
{
	struct amdgpu_device *adev = psp->adev;
	int ret;

	if (!amdgpu_sriov_vf(adev) || !adev->in_gpu_reset) {
		ret = psp_bootloader_load_sysdrv(psp);
		if (ret)
			return ret;

		ret = psp_bootloader_load_sos(psp);
		if (ret)
			return ret;
	}

	ret = psp_ring_create(psp, PSP_RING_TYPE__KM);
	if (ret)
		return ret;

	ret = psp_tmr_load(psp);
	if (ret)
		return ret;

	ret = psp_asd_load(psp);
	if (ret)
		return ret;

	return 0;
}