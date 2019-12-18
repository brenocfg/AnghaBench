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
typedef  int /*<<< orphan*/  uint32_t ;
struct smu_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_MSG_GetCurrentRpm ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  smu_read_smc_arg (struct smu_context*,int /*<<< orphan*/ *) ; 
 int smu_send_smc_msg (struct smu_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega20_get_fan_speed_rpm(struct smu_context *smu,
				    uint32_t *speed)
{
	int ret;

	ret = smu_send_smc_msg(smu, SMU_MSG_GetCurrentRpm);

	if (ret) {
		pr_err("Attempt to get current RPM from SMC Failed!\n");
		return ret;
	}

	smu_read_smc_arg(smu, speed);

	return 0;
}