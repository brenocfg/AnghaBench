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
typedef  int /*<<< orphan*/  suspend_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ROCKCHIP_ARM_OFF_LOGIC_NORMAL ; 
 int /*<<< orphan*/  cpu_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  local_fiq_enable () ; 
 int /*<<< orphan*/  rk3288_slp_mode_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk3288_slp_mode_set_resume () ; 
 int /*<<< orphan*/  rockchip_lpmode_enter ; 

__attribute__((used)) static int rk3288_suspend_enter(suspend_state_t state)
{
	local_fiq_disable();

	rk3288_slp_mode_set(ROCKCHIP_ARM_OFF_LOGIC_NORMAL);

	cpu_suspend(0, rockchip_lpmode_enter);

	rk3288_slp_mode_set_resume();

	local_fiq_enable();

	return 0;
}