#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct smu_context {int dummy; } ;
typedef  enum amd_pp_sensors { ____Placeholder_amd_pp_sensors } amd_pp_sensors ;
struct TYPE_3__ {int /*<<< orphan*/  AverageUclkActivity; int /*<<< orphan*/  AverageGfxActivity; } ;
typedef  TYPE_1__ SmuMetrics_t ;

/* Variables and functions */
#define  AMDGPU_PP_SENSOR_GPU_LOAD 129 
#define  AMDGPU_PP_SENSOR_MEM_LOAD 128 
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int vega20_get_metrics_table (struct smu_context*,TYPE_1__*) ; 

__attribute__((used)) static int vega20_get_current_activity_percent(struct smu_context *smu,
					       enum amd_pp_sensors sensor,
					       uint32_t *value)
{
	int ret = 0;
	SmuMetrics_t metrics;

	if (!value)
		return -EINVAL;

	ret = vega20_get_metrics_table(smu, &metrics);
	if (ret)
		return ret;

	switch (sensor) {
	case AMDGPU_PP_SENSOR_GPU_LOAD:
		*value = metrics.AverageGfxActivity;
		break;
	case AMDGPU_PP_SENSOR_MEM_LOAD:
		*value = metrics.AverageUclkActivity;
		break;
	default:
		pr_err("Invalid sensor for retrieving clock activity\n");
		return -EINVAL;
	}

	return 0;
}