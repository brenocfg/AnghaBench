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
struct smu_table_context {scalar_t__ metrics_table; scalar_t__ metrics_time; } ;
struct smu_context {struct smu_table_context smu_table; } ;
typedef  int /*<<< orphan*/  SmuMetrics_t ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  SMU_TABLE_SMU_METRICS ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int smu_update_table (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int vega20_get_metrics_table(struct smu_context *smu,
				    SmuMetrics_t *metrics_table)
{
	struct smu_table_context *smu_table= &smu->smu_table;
	int ret = 0;

	if (!smu_table->metrics_time || time_after(jiffies, smu_table->metrics_time + HZ / 1000)) {
		ret = smu_update_table(smu, SMU_TABLE_SMU_METRICS, 0,
				(void *)smu_table->metrics_table, false);
		if (ret) {
			pr_info("Failed to export SMU metrics table!\n");
			return ret;
		}
		smu_table->metrics_time = jiffies;
	}

	memcpy(metrics_table, smu_table->metrics_table, sizeof(SmuMetrics_t));

	return ret;
}