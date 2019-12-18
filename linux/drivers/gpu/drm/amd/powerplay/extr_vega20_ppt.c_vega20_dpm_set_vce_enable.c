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
struct smu_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_FEATURE_DPM_VCE_BIT ; 
 int smu_feature_is_enabled (struct smu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu_feature_is_supported (struct smu_context*,int /*<<< orphan*/ ) ; 
 int smu_feature_set_enabled (struct smu_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vega20_dpm_set_vce_enable(struct smu_context *smu, bool enable)
{
	if (!smu_feature_is_supported(smu, SMU_FEATURE_DPM_VCE_BIT))
		return 0;

	if (enable == smu_feature_is_enabled(smu, SMU_FEATURE_DPM_VCE_BIT))
		return 0;

	return smu_feature_set_enabled(smu, SMU_FEATURE_DPM_VCE_BIT, enable);
}