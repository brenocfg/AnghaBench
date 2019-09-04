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
typedef  int uint32_t ;
struct cgs_device {int dummy; } ;
typedef  enum AMDGPU_UCODE_ID { ____Placeholder_AMDGPU_UCODE_ID } AMDGPU_UCODE_ID ;
struct TYPE_2__ {int /*<<< orphan*/  asic_type; } ;

/* Variables and functions */
 int AMDGPU_UCODE_ID_CP_CE ; 
 int AMDGPU_UCODE_ID_CP_ME ; 
 int AMDGPU_UCODE_ID_CP_MEC1 ; 
 int AMDGPU_UCODE_ID_CP_MEC2 ; 
 int AMDGPU_UCODE_ID_CP_PFP ; 
 int AMDGPU_UCODE_ID_MAXIMUM ; 
 int AMDGPU_UCODE_ID_RLC_G ; 
 int AMDGPU_UCODE_ID_SDMA0 ; 
 int AMDGPU_UCODE_ID_SDMA1 ; 
 int AMDGPU_UCODE_ID_STORAGE ; 
 int /*<<< orphan*/  CGS_FUNC_ADEV ; 
#define  CGS_UCODE_ID_CP_CE 137 
#define  CGS_UCODE_ID_CP_ME 136 
#define  CGS_UCODE_ID_CP_MEC 135 
#define  CGS_UCODE_ID_CP_MEC_JT1 134 
#define  CGS_UCODE_ID_CP_MEC_JT2 133 
#define  CGS_UCODE_ID_CP_PFP 132 
#define  CGS_UCODE_ID_RLC_G 131 
#define  CGS_UCODE_ID_SDMA0 130 
#define  CGS_UCODE_ID_SDMA1 129 
#define  CGS_UCODE_ID_STORAGE 128 
 int /*<<< orphan*/  CHIP_TOPAZ ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 TYPE_1__* adev ; 

__attribute__((used)) static uint32_t fw_type_convert(struct cgs_device *cgs_device, uint32_t fw_type)
{
	CGS_FUNC_ADEV;
	enum AMDGPU_UCODE_ID result = AMDGPU_UCODE_ID_MAXIMUM;

	switch (fw_type) {
	case CGS_UCODE_ID_SDMA0:
		result = AMDGPU_UCODE_ID_SDMA0;
		break;
	case CGS_UCODE_ID_SDMA1:
		result = AMDGPU_UCODE_ID_SDMA1;
		break;
	case CGS_UCODE_ID_CP_CE:
		result = AMDGPU_UCODE_ID_CP_CE;
		break;
	case CGS_UCODE_ID_CP_PFP:
		result = AMDGPU_UCODE_ID_CP_PFP;
		break;
	case CGS_UCODE_ID_CP_ME:
		result = AMDGPU_UCODE_ID_CP_ME;
		break;
	case CGS_UCODE_ID_CP_MEC:
	case CGS_UCODE_ID_CP_MEC_JT1:
		result = AMDGPU_UCODE_ID_CP_MEC1;
		break;
	case CGS_UCODE_ID_CP_MEC_JT2:
		/* for VI. JT2 should be the same as JT1, because:
			1, MEC2 and MEC1 use exactly same FW.
			2, JT2 is not pached but JT1 is.
		*/
		if (adev->asic_type >= CHIP_TOPAZ)
			result = AMDGPU_UCODE_ID_CP_MEC1;
		else
			result = AMDGPU_UCODE_ID_CP_MEC2;
		break;
	case CGS_UCODE_ID_RLC_G:
		result = AMDGPU_UCODE_ID_RLC_G;
		break;
	case CGS_UCODE_ID_STORAGE:
		result = AMDGPU_UCODE_ID_STORAGE;
		break;
	default:
		DRM_ERROR("Firmware type not supported\n");
	}
	return result;
}