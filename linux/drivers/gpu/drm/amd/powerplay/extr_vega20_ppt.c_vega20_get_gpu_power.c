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
typedef  int uint32_t ;
struct smu_context {int dummy; } ;
struct TYPE_3__ {int AverageSocketPower; int CurrSocketPower; } ;
typedef  TYPE_1__ SmuMetrics_t ;

/* Variables and functions */
 int EINVAL ; 
 int smu_get_smc_version (struct smu_context*,int /*<<< orphan*/ *,int*) ; 
 int vega20_get_metrics_table (struct smu_context*,TYPE_1__*) ; 

__attribute__((used)) static int vega20_get_gpu_power(struct smu_context *smu, uint32_t *value)
{
	uint32_t smu_version;
	int ret = 0;
	SmuMetrics_t metrics;

	if (!value)
		return -EINVAL;

	ret = vega20_get_metrics_table(smu, &metrics);
	if (ret)
		return ret;

	ret = smu_get_smc_version(smu, NULL, &smu_version);
	if (ret)
		return ret;

	/* For the 40.46 release, they changed the value name */
	if (smu_version == 0x282e00)
		*value = metrics.AverageSocketPower << 8;
	else
		*value = metrics.CurrSocketPower << 8;

	return 0;
}