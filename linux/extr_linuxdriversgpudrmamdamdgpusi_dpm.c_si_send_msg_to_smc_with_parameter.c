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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {int dummy; } ;
typedef  int /*<<< orphan*/  PPSMC_Result ;
typedef  int /*<<< orphan*/  PPSMC_Msg ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_SCRATCH0 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_si_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PPSMC_Result si_send_msg_to_smc_with_parameter(struct amdgpu_device *adev,
						      PPSMC_Msg msg, u32 parameter)
{
	WREG32(SMC_SCRATCH0, parameter);
	return amdgpu_si_send_msg_to_smc(adev, msg);
}