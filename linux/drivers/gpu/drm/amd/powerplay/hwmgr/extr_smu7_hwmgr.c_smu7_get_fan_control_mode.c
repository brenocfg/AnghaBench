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
typedef  int /*<<< orphan*/  uint32_t ;
struct pp_hwmgr {scalar_t__ fan_ctrl_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_FAN_CTRL_AUTO ; 
 int /*<<< orphan*/  AMD_FAN_CTRL_MANUAL ; 

__attribute__((used)) static uint32_t smu7_get_fan_control_mode(struct pp_hwmgr *hwmgr)
{
	return hwmgr->fan_ctrl_enabled ? AMD_FAN_CTRL_AUTO : AMD_FAN_CTRL_MANUAL;
}