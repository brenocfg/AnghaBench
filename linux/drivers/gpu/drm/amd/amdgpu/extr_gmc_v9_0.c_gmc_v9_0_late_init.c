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
struct TYPE_4__ {int /*<<< orphan*/  vm_fault; } ;
struct amdgpu_device {int asic_type; TYPE_2__ gmc; TYPE_1__* df_funcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable_ecc_force_par_wr_rmw ) (struct amdgpu_device*,int) ;} ;

/* Variables and functions */
#define  CHIP_VEGA10 129 
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int amdgpu_atomfirmware_mem_ecc_supported (struct amdgpu_device*) ; 
 int amdgpu_atomfirmware_sram_ecc_supported (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_bo_late_init (struct amdgpu_device*) ; 
 int amdgpu_irq_get (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int gmc_v9_0_allocate_vm_inv_eng (struct amdgpu_device*) ; 
 int gmc_v9_0_ecc_late_init (void*) ; 
 int /*<<< orphan*/  gmc_v9_0_keep_stolen_memory (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*,int) ; 

__attribute__((used)) static int gmc_v9_0_late_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	bool r;

	if (!gmc_v9_0_keep_stolen_memory(adev))
		amdgpu_bo_late_init(adev);

	r = gmc_v9_0_allocate_vm_inv_eng(adev);
	if (r)
		return r;
	/* Check if ecc is available */
	if (!amdgpu_sriov_vf(adev)) {
		switch (adev->asic_type) {
		case CHIP_VEGA10:
		case CHIP_VEGA20:
			r = amdgpu_atomfirmware_mem_ecc_supported(adev);
			if (!r) {
				DRM_INFO("ECC is not present.\n");
				if (adev->df_funcs->enable_ecc_force_par_wr_rmw)
					adev->df_funcs->enable_ecc_force_par_wr_rmw(adev, false);
			} else {
				DRM_INFO("ECC is active.\n");
			}

			r = amdgpu_atomfirmware_sram_ecc_supported(adev);
			if (!r) {
				DRM_INFO("SRAM ECC is not present.\n");
			} else {
				DRM_INFO("SRAM ECC is active.\n");
			}
			break;
		default:
			break;
		}
	}

	r = gmc_v9_0_ecc_late_init(handle);
	if (r)
		return r;

	return amdgpu_irq_get(adev, &adev->gmc.vm_fault, 0);
}