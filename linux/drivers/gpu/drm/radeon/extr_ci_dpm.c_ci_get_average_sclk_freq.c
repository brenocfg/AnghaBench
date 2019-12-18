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
typedef  scalar_t__ u32 ;
struct radeon_device {int dummy; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_API_GetSclkFrequency ; 
 scalar_t__ PPSMC_Result_OK ; 
 scalar_t__ ci_send_msg_to_smc_return_parameter (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static u32 ci_get_average_sclk_freq(struct radeon_device *rdev)
{
	u32 sclk_freq;
	PPSMC_Result smc_result =
		ci_send_msg_to_smc_return_parameter(rdev,
						    PPSMC_MSG_API_GetSclkFrequency,
						    &sclk_freq);
	if (smc_result != PPSMC_Result_OK)
		sclk_freq = 0;

	return sclk_freq;
}