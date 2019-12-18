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
typedef  enum smu_v11_0_baco_seq { ____Placeholder_smu_v11_0_baco_seq } smu_v11_0_baco_seq ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_MSG_ArmD3 ; 
 int smu_send_smc_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu_v11_0_baco_set_armd3_sequence(struct smu_context *smu, enum smu_v11_0_baco_seq baco_seq)
{
	return smu_send_smc_msg_with_param(smu, SMU_MSG_ArmD3, baco_seq);
}