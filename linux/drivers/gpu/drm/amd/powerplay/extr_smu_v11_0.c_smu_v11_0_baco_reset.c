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
struct smu_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACO_SEQ_BACO ; 
 int /*<<< orphan*/  SMU_BACO_STATE_ENTER ; 
 int /*<<< orphan*/  SMU_BACO_STATE_EXIT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int smu_v11_0_baco_set_armd3_sequence (struct smu_context*,int /*<<< orphan*/ ) ; 
 int smu_v11_0_baco_set_state (struct smu_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu_v11_0_baco_reset(struct smu_context *smu)
{
	int ret = 0;

	ret = smu_v11_0_baco_set_armd3_sequence(smu, BACO_SEQ_BACO);
	if (ret)
		return ret;

	ret = smu_v11_0_baco_set_state(smu, SMU_BACO_STATE_ENTER);
	if (ret)
		return ret;

	msleep(10);

	ret = smu_v11_0_baco_set_state(smu, SMU_BACO_STATE_EXIT);
	if (ret)
		return ret;

	return ret;
}