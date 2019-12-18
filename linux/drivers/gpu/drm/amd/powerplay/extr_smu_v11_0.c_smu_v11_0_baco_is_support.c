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
typedef  int uint32_t ;
struct smu_baco_context {int platform_support; int /*<<< orphan*/  mutex; } ;
struct smu_context {struct smu_baco_context smu_baco; struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBIO ; 
 int RCC_BIF_STRAP0__STRAP_PX_CAPABLE_MASK ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU_FEATURE_BACO_BIT ; 
 int /*<<< orphan*/  mmRCC_BIF_STRAP0 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smu_feature_is_enabled (struct smu_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool smu_v11_0_baco_is_support(struct smu_context *smu)
{
	struct amdgpu_device *adev = smu->adev;
	struct smu_baco_context *smu_baco = &smu->smu_baco;
	uint32_t val;
	bool baco_support;

	mutex_lock(&smu_baco->mutex);
	baco_support = smu_baco->platform_support;
	mutex_unlock(&smu_baco->mutex);

	if (!baco_support)
		return false;

	if (!smu_feature_is_enabled(smu, SMU_FEATURE_BACO_BIT))
		return false;

	val = RREG32_SOC15(NBIO, 0, mmRCC_BIF_STRAP0);
	if (val & RCC_BIF_STRAP0__STRAP_PX_CAPABLE_MASK)
		return true;

	return false;
}