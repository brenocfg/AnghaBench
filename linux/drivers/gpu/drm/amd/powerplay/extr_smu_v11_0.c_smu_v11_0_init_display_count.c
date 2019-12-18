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
struct smu_context {int /*<<< orphan*/  pm_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_MSG_NumOfDisplays ; 
 int smu_send_smc_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu_v11_0_init_display_count(struct smu_context *smu, uint32_t count)
{
	int ret = 0;

	if (!smu->pm_enabled)
		return ret;

	ret = smu_send_smc_msg_with_param(smu, SMU_MSG_NumOfDisplays, count);
	return ret;
}