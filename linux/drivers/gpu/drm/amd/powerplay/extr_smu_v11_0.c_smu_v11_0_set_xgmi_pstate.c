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
typedef  scalar_t__ uint32_t ;
struct smu_context {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_MSG_SetXgmiMode ; 
 int /*<<< orphan*/  XGMI_STATE_D0 ; 
 int /*<<< orphan*/  XGMI_STATE_D3 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smu_send_smc_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu_v11_0_set_xgmi_pstate(struct smu_context *smu,
				     uint32_t pstate)
{
	int ret = 0;
	mutex_lock(&(smu->mutex));
	ret = smu_send_smc_msg_with_param(smu,
					  SMU_MSG_SetXgmiMode,
					  pstate ? XGMI_STATE_D0 : XGMI_STATE_D3);
	mutex_unlock(&(smu->mutex));
	return ret;
}