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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct smu_context {int dummy; } ;

/* Variables and functions */
 unsigned long SMC_DPM_FEATURE ; 
 int smu_feature_get_enabled_mask (struct smu_context*,scalar_t__*,int) ; 

__attribute__((used)) static bool arcturus_is_dpm_running(struct smu_context *smu)
{
	int ret = 0;
	uint32_t feature_mask[2];
	unsigned long feature_enabled;
	ret = smu_feature_get_enabled_mask(smu, feature_mask, 2);
	feature_enabled = (unsigned long)((uint64_t)feature_mask[0] |
			   ((uint64_t)feature_mask[1] << 32));
	return !!(feature_enabled & SMC_DPM_FEATURE);
}