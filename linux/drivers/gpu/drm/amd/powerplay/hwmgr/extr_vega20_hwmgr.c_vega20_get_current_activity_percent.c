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
struct pp_hwmgr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  AverageUclkActivity; int /*<<< orphan*/  AverageGfxActivity; } ;
typedef  TYPE_1__ SmuMetrics_t ;

/* Variables and functions */
#define  AMDGPU_PP_SENSOR_GPU_LOAD 129 
#define  AMDGPU_PP_SENSOR_MEM_LOAD 128 
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int vega20_get_metrics_table (struct pp_hwmgr*,TYPE_1__*) ; 

__attribute__((used)) static int vega20_get_current_activity_percent(struct pp_hwmgr *hwmgr,
		int idx,
		uint32_t *activity_percent)
{
	int ret = 0;
	SmuMetrics_t metrics_table;

	ret = vega20_get_metrics_table(hwmgr, &metrics_table);
	if (ret)
		return ret;

	switch (idx) {
	case AMDGPU_PP_SENSOR_GPU_LOAD:
		*activity_percent = metrics_table.AverageGfxActivity;
		break;
	case AMDGPU_PP_SENSOR_MEM_LOAD:
		*activity_percent = metrics_table.AverageUclkActivity;
		break;
	default:
		pr_err("Invalid index for retrieving clock activity\n");
		return -EINVAL;
	}

	return ret;
}