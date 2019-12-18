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
struct amdgpu_device {int asic_type; } ;

/* Variables and functions */
#define  CHIP_NAVI10 130 
#define  CHIP_NAVI12 129 
#define  CHIP_NAVI14 128 
 int /*<<< orphan*/  DRM_WARN (char*) ; 
 int EINVAL ; 
 scalar_t__ amdgpu_discovery ; 
 int amdgpu_discovery_reg_base_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  navi10_reg_base_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  navi12_reg_base_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  navi14_reg_base_init (struct amdgpu_device*) ; 

__attribute__((used)) static int nv_reg_base_init(struct amdgpu_device *adev)
{
	int r;

	if (amdgpu_discovery) {
		r = amdgpu_discovery_reg_base_init(adev);
		if (r) {
			DRM_WARN("failed to init reg base from ip discovery table, "
					"fallback to legacy init method\n");
			goto legacy_init;
		}

		return 0;
	}

legacy_init:
	switch (adev->asic_type) {
	case CHIP_NAVI10:
		navi10_reg_base_init(adev);
		break;
	case CHIP_NAVI14:
		navi14_reg_base_init(adev);
		break;
	case CHIP_NAVI12:
		navi12_reg_base_init(adev);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}