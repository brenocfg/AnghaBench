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
struct psp_context {struct amdgpu_device* adev; } ;
struct TYPE_2__ {scalar_t__ load_type; } ;
struct amdgpu_device {int asic_type; TYPE_1__ firmware; struct psp_context psp; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
#define  CHIP_RAVEN 131 
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int psp_init_microcode (struct psp_context*) ; 
 int /*<<< orphan*/  psp_v10_0_set_psp_funcs (struct psp_context*) ; 
 int /*<<< orphan*/  psp_v3_1_set_psp_funcs (struct psp_context*) ; 

__attribute__((used)) static int psp_sw_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct psp_context *psp = &adev->psp;
	int ret;

	switch (adev->asic_type) {
	case CHIP_VEGA10:
	case CHIP_VEGA12:
	case CHIP_VEGA20:
		psp_v3_1_set_psp_funcs(psp);
		break;
	case CHIP_RAVEN:
		psp_v10_0_set_psp_funcs(psp);
		break;
	default:
		return -EINVAL;
	}

	psp->adev = adev;

	if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP)
		return 0;

	ret = psp_init_microcode(psp);
	if (ret) {
		DRM_ERROR("Failed to load psp firmware!\n");
		return ret;
	}

	return 0;
}