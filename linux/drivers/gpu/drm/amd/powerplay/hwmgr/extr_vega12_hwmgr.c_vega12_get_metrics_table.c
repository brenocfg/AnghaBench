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
typedef  int /*<<< orphan*/  uint8_t ;
struct vega12_hwmgr {int /*<<< orphan*/  metrics_table; scalar_t__ metrics_time; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
typedef  int /*<<< orphan*/  SmuMetrics_t ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  TABLE_SMU_METRICS ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int smum_smc_table_manager (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int vega12_get_metrics_table(struct pp_hwmgr *hwmgr, SmuMetrics_t *metrics_table)
{
	struct vega12_hwmgr *data =
			(struct vega12_hwmgr *)(hwmgr->backend);
	int ret = 0;

	if (!data->metrics_time || time_after(jiffies, data->metrics_time + HZ / 2)) {
		ret = smum_smc_table_manager(hwmgr, (uint8_t *)metrics_table,
				TABLE_SMU_METRICS, true);
		if (ret) {
			pr_info("Failed to export SMU metrics table!\n");
			return ret;
		}
		memcpy(&data->metrics_table, metrics_table, sizeof(SmuMetrics_t));
		data->metrics_time = jiffies;
	} else
		memcpy(metrics_table, &data->metrics_table, sizeof(SmuMetrics_t));

	return ret;
}