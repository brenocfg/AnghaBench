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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSMU ; 
 int /*<<< orphan*/  RSMU_UMC_INDEX_MODE_EN ; 
 int /*<<< orphan*/  RSMU_UMC_INDEX_REGISTER_NBIF_VG20_GPU ; 
 int /*<<< orphan*/  WREG32_FIELD15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void umc_v6_1_disable_umc_index_mode(struct amdgpu_device *adev)
{
	WREG32_FIELD15(RSMU, 0, RSMU_UMC_INDEX_REGISTER_NBIF_VG20_GPU,
			RSMU_UMC_INDEX_MODE_EN, 0);
}