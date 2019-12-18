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
struct TYPE_3__ {int /*<<< orphan*/  CurrFanSpeed; } ;
typedef  TYPE_1__ SmuMetrics_t ;

/* Variables and functions */
 int EINVAL ; 
 int navi10_get_metrics_table (struct smu_context*,TYPE_1__*) ; 

__attribute__((used)) static int navi10_get_fan_speed_rpm(struct smu_context *smu,
				    uint32_t *speed)
{
	SmuMetrics_t metrics;
	int ret = 0;

	if (!speed)
		return -EINVAL;

	ret = navi10_get_metrics_table(smu, &metrics);
	if (ret)
		return ret;

	*speed = metrics.CurrFanSpeed;

	return ret;
}