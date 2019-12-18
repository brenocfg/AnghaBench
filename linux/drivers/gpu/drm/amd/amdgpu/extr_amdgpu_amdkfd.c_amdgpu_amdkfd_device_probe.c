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
struct kgd_dev {int dummy; } ;
struct kfd2kgd_calls {int dummy; } ;
struct TYPE_3__ {scalar_t__ real_vram_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct amdgpu_device {int asic_type; TYPE_1__ gmc; TYPE_2__ kfd; int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CHIP_ARCTURUS 144 
#define  CHIP_CARRIZO 143 
#define  CHIP_FIJI 142 
#define  CHIP_HAWAII 141 
#define  CHIP_KAVERI 140 
#define  CHIP_NAVI10 139 
#define  CHIP_NAVI12 138 
#define  CHIP_NAVI14 137 
#define  CHIP_POLARIS10 136 
#define  CHIP_POLARIS11 135 
#define  CHIP_POLARIS12 134 
#define  CHIP_RAVEN 133 
#define  CHIP_TONGA 132 
#define  CHIP_VEGA10 131 
#define  CHIP_VEGA12 130 
#define  CHIP_VEGA20 129 
#define  CHIP_VEGAM 128 
 struct kfd2kgd_calls* amdgpu_amdkfd_arcturus_get_functions () ; 
 struct kfd2kgd_calls* amdgpu_amdkfd_gfx_10_0_get_functions () ; 
 struct kfd2kgd_calls* amdgpu_amdkfd_gfx_7_get_functions () ; 
 struct kfd2kgd_calls* amdgpu_amdkfd_gfx_8_0_get_functions () ; 
 struct kfd2kgd_calls* amdgpu_amdkfd_gfx_9_0_get_functions () ; 
 int /*<<< orphan*/  amdgpu_amdkfd_total_mem_size ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kgd2kfd_probe (struct kgd_dev*,int /*<<< orphan*/ ,struct kfd2kgd_calls const*) ; 

void amdgpu_amdkfd_device_probe(struct amdgpu_device *adev)
{
	const struct kfd2kgd_calls *kfd2kgd;

	switch (adev->asic_type) {
#ifdef CONFIG_DRM_AMDGPU_CIK
	case CHIP_KAVERI:
	case CHIP_HAWAII:
		kfd2kgd = amdgpu_amdkfd_gfx_7_get_functions();
		break;
#endif
	case CHIP_CARRIZO:
	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
	case CHIP_VEGAM:
		kfd2kgd = amdgpu_amdkfd_gfx_8_0_get_functions();
		break;
	case CHIP_VEGA10:
	case CHIP_VEGA12:
	case CHIP_VEGA20:
	case CHIP_RAVEN:
		kfd2kgd = amdgpu_amdkfd_gfx_9_0_get_functions();
		break;
	case CHIP_ARCTURUS:
		kfd2kgd = amdgpu_amdkfd_arcturus_get_functions();
		break;
	case CHIP_NAVI10:
	case CHIP_NAVI14:
	case CHIP_NAVI12:
		kfd2kgd = amdgpu_amdkfd_gfx_10_0_get_functions();
		break;
	default:
		dev_info(adev->dev, "kfd not supported on this ASIC\n");
		return;
	}

	adev->kfd.dev = kgd2kfd_probe((struct kgd_dev *)adev,
				      adev->pdev, kfd2kgd);

	if (adev->kfd.dev)
		amdgpu_amdkfd_total_mem_size += adev->gmc.real_vram_size;
}