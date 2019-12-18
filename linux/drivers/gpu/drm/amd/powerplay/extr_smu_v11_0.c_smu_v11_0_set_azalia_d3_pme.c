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
struct smu_context {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_MSG_BacoAudioD3PME ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smu_send_smc_msg (struct smu_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu_v11_0_set_azalia_d3_pme(struct smu_context *smu)
{
	int ret = 0;

	mutex_lock(&smu->mutex);
	ret = smu_send_smc_msg(smu, SMU_MSG_BacoAudioD3PME);
	mutex_unlock(&smu->mutex);

	return ret;
}