#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int platform_caps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int ATOM_PP_PLATFORM_CAP_REGULATOR_HOT ; 
 int /*<<< orphan*/  PPSMC_MSG_EnableVRHotGPIOInterrupt ; 
 int /*<<< orphan*/  ci_send_msg_to_smc (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ci_enable_vr_hot_gpio_interrupt(struct radeon_device *rdev)
{
	if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_REGULATOR_HOT)
		ci_send_msg_to_smc(rdev, PPSMC_MSG_EnableVRHotGPIOInterrupt);
}