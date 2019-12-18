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
struct amdgpu_device {int pg_flags; int asic_type; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_SDMA ; 
#define  CHIP_RAVEN 129 
#define  CHIP_RENOIR 128 
 int /*<<< orphan*/  sdma_v4_1_init_power_gating (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sdma_v4_1_update_power_gating (struct amdgpu_device*,int) ; 

__attribute__((used)) static void sdma_v4_0_init_pg(struct amdgpu_device *adev)
{
	if (!(adev->pg_flags & AMD_PG_SUPPORT_SDMA))
		return;

	switch (adev->asic_type) {
	case CHIP_RAVEN:
	case CHIP_RENOIR:
		sdma_v4_1_init_power_gating(adev);
		sdma_v4_1_update_power_gating(adev, true);
		break;
	default:
		break;
	}
}