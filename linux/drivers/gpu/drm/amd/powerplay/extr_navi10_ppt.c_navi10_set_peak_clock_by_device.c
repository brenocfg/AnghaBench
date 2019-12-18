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
typedef  scalar_t__ uint32_t ;
struct smu_context {struct amdgpu_device* adev; } ;
struct amdgpu_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int revision; } ;

/* Variables and functions */
 scalar_t__ NAVI10_PEAK_SCLK_XL ; 
 scalar_t__ NAVI10_PEAK_SCLK_XT ; 
 scalar_t__ NAVI10_PEAK_SCLK_XTX ; 
 int /*<<< orphan*/  SMU_SCLK ; 
 int /*<<< orphan*/  SMU_UCLK ; 
 int smu_get_dpm_freq_by_index (struct smu_context*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int smu_get_dpm_level_count (struct smu_context*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int smu_set_soft_freq_range (struct smu_context*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int navi10_set_peak_clock_by_device(struct smu_context *smu)
{
	struct amdgpu_device *adev = smu->adev;
	int ret = 0;
	uint32_t sclk_freq = 0, uclk_freq = 0;
	uint32_t uclk_level = 0;

	switch (adev->pdev->revision) {
	case 0xf0: /* XTX */
	case 0xc0:
		sclk_freq = NAVI10_PEAK_SCLK_XTX;
		break;
	case 0xf1: /* XT */
	case 0xc1:
		sclk_freq = NAVI10_PEAK_SCLK_XT;
		break;
	default: /* XL */
		sclk_freq = NAVI10_PEAK_SCLK_XL;
		break;
	}

	ret = smu_get_dpm_level_count(smu, SMU_UCLK, &uclk_level);
	if (ret)
		return ret;
	ret = smu_get_dpm_freq_by_index(smu, SMU_UCLK, uclk_level - 1, &uclk_freq);
	if (ret)
		return ret;

	ret = smu_set_soft_freq_range(smu, SMU_SCLK, sclk_freq, sclk_freq);
	if (ret)
		return ret;
	ret = smu_set_soft_freq_range(smu, SMU_UCLK, uclk_freq, uclk_freq);
	if (ret)
		return ret;

	return ret;
}