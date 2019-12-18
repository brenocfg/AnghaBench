#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smu_context {TYPE_1__* adev; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int /*<<< orphan*/  SMU_MSG_PowerDownVcn ; 
 int /*<<< orphan*/  SMU_MSG_PowerUpVcn ; 
 int smu_send_smc_msg (struct smu_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu_v12_0_powergate_vcn(struct smu_context *smu, bool gate)
{
	if (!(smu->adev->flags & AMD_IS_APU))
		return 0;

	if (gate)
		return smu_send_smc_msg(smu, SMU_MSG_PowerDownVcn);
	else
		return smu_send_smc_msg(smu, SMU_MSG_PowerUpVcn);
}