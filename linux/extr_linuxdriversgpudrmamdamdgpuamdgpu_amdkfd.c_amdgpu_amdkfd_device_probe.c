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
struct kgd_dev {int dummy; } ;
struct kfd2kgd_calls {int dummy; } ;
struct amdgpu_device {int asic_type; int /*<<< orphan*/  pdev; int /*<<< orphan*/  kfd; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* probe ) (struct kgd_dev*,int /*<<< orphan*/ ,struct kfd2kgd_calls const*) ;} ;

/* Variables and functions */
#define  CHIP_CARRIZO 134 
#define  CHIP_FIJI 133 
#define  CHIP_POLARIS10 132 
#define  CHIP_POLARIS11 131 
#define  CHIP_RAVEN 130 
#define  CHIP_TONGA 129 
#define  CHIP_VEGA10 128 
 struct kfd2kgd_calls* amdgpu_amdkfd_gfx_8_0_get_functions () ; 
 struct kfd2kgd_calls* amdgpu_amdkfd_gfx_9_0_get_functions () ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* kgd2kfd ; 
 int /*<<< orphan*/  stub1 (struct kgd_dev*,int /*<<< orphan*/ ,struct kfd2kgd_calls const*) ; 

void amdgpu_amdkfd_device_probe(struct amdgpu_device *adev)
{
	const struct kfd2kgd_calls *kfd2kgd;

	if (!kgd2kfd)
		return;

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
		kfd2kgd = amdgpu_amdkfd_gfx_8_0_get_functions();
		break;
	case CHIP_VEGA10:
	case CHIP_RAVEN:
		kfd2kgd = amdgpu_amdkfd_gfx_9_0_get_functions();
		break;
	default:
		dev_info(adev->dev, "kfd not supported on this ASIC\n");
		return;
	}

	adev->kfd = kgd2kfd->probe((struct kgd_dev *)adev,
				   adev->pdev, kfd2kgd);
}