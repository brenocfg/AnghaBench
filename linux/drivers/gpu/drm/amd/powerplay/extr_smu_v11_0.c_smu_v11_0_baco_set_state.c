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
struct smu_baco_context {int state; int /*<<< orphan*/  mutex; } ;
struct smu_context {struct smu_baco_context smu_baco; } ;
typedef  enum smu_baco_state { ____Placeholder_smu_baco_state } smu_baco_state ;

/* Variables and functions */
 int /*<<< orphan*/  BACO_SEQ_BACO ; 
 int SMU_BACO_STATE_ENTER ; 
 int /*<<< orphan*/  SMU_MSG_EnterBaco ; 
 int /*<<< orphan*/  SMU_MSG_ExitBaco ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smu_send_smc_msg (struct smu_context*,int /*<<< orphan*/ ) ; 
 int smu_send_smc_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smu_v11_0_baco_get_state (struct smu_context*) ; 

__attribute__((used)) static int smu_v11_0_baco_set_state(struct smu_context *smu, enum smu_baco_state state)
{

	struct smu_baco_context *smu_baco = &smu->smu_baco;
	int ret = 0;

	if (smu_v11_0_baco_get_state(smu) == state)
		return 0;

	mutex_lock(&smu_baco->mutex);

	if (state == SMU_BACO_STATE_ENTER)
		ret = smu_send_smc_msg_with_param(smu, SMU_MSG_EnterBaco, BACO_SEQ_BACO);
	else
		ret = smu_send_smc_msg(smu, SMU_MSG_ExitBaco);
	if (ret)
		goto out;

	smu_baco->state = state;
out:
	mutex_unlock(&smu_baco->mutex);
	return ret;
}