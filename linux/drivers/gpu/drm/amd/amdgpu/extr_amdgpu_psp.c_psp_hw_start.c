#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct psp_context {struct amdgpu_device* adev; TYPE_1__* funcs; scalar_t__ kdb_bin_size; } ;
struct TYPE_8__ {scalar_t__ ta_fw; } ;
struct TYPE_6__ {int num_physical_nodes; } ;
struct TYPE_7__ {TYPE_2__ xgmi; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; TYPE_4__ psp; TYPE_3__ gmc; int /*<<< orphan*/  in_gpu_reset; } ;
struct TYPE_5__ {int /*<<< orphan*/ * bootloader_load_kdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  PSP_RING_TYPE__KM ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int psp_asd_init (struct psp_context*) ; 
 int psp_asd_load (struct psp_context*) ; 
 int psp_bootloader_load_kdb (struct psp_context*) ; 
 int psp_bootloader_load_sos (struct psp_context*) ; 
 int psp_bootloader_load_sysdrv (struct psp_context*) ; 
 int psp_ras_initialize (struct psp_context*) ; 
 int psp_ring_create (struct psp_context*,int /*<<< orphan*/ ) ; 
 int psp_tmr_init (struct psp_context*) ; 
 int psp_tmr_load (struct psp_context*) ; 
 int psp_xgmi_initialize (struct psp_context*) ; 

__attribute__((used)) static int psp_hw_start(struct psp_context *psp)
{
	struct amdgpu_device *adev = psp->adev;
	int ret;

	if (!amdgpu_sriov_vf(adev) || !adev->in_gpu_reset) {
		if (psp->kdb_bin_size &&
		    (psp->funcs->bootloader_load_kdb != NULL)) {
			ret = psp_bootloader_load_kdb(psp);
			if (ret) {
				DRM_ERROR("PSP load kdb failed!\n");
				return ret;
			}
		}

		ret = psp_bootloader_load_sysdrv(psp);
		if (ret) {
			DRM_ERROR("PSP load sysdrv failed!\n");
			return ret;
		}

		ret = psp_bootloader_load_sos(psp);
		if (ret) {
			DRM_ERROR("PSP load sos failed!\n");
			return ret;
		}
	}

	ret = psp_ring_create(psp, PSP_RING_TYPE__KM);
	if (ret) {
		DRM_ERROR("PSP create ring failed!\n");
		return ret;
	}

	ret = psp_tmr_init(psp);
	if (ret) {
		DRM_ERROR("PSP tmr init failed!\n");
		return ret;
	}

	ret = psp_tmr_load(psp);
	if (ret) {
		DRM_ERROR("PSP load tmr failed!\n");
		return ret;
	}

	ret = psp_asd_init(psp);
	if (ret) {
		DRM_ERROR("PSP asd init failed!\n");
		return ret;
	}

	ret = psp_asd_load(psp);
	if (ret) {
		DRM_ERROR("PSP load asd failed!\n");
		return ret;
	}

	if (adev->gmc.xgmi.num_physical_nodes > 1) {
		ret = psp_xgmi_initialize(psp);
		/* Warning the XGMI seesion initialize failure
		 * Instead of stop driver initialization
		 */
		if (ret)
			dev_err(psp->adev->dev,
				"XGMI: Failed to initialize XGMI session\n");
	}

	if (psp->adev->psp.ta_fw) {
		ret = psp_ras_initialize(psp);
		if (ret)
			dev_err(psp->adev->dev,
					"RAS: Failed to initialize RAS\n");
	}

	return 0;
}