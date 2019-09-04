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
struct pp_hwmgr {int dummy; } ;
struct phm_fan_speed_info {int supports_percent_read; int supports_percent_write; int supports_rpm_read; int supports_rpm_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct phm_fan_speed_info*,int /*<<< orphan*/ ,int) ; 

int vega12_fan_ctrl_get_fan_speed_info(struct pp_hwmgr *hwmgr,
		struct phm_fan_speed_info *fan_speed_info)
{
	memset(fan_speed_info, 0, sizeof(*fan_speed_info));
	fan_speed_info->supports_percent_read = false;
	fan_speed_info->supports_percent_write = false;
	fan_speed_info->supports_rpm_read = true;
	fan_speed_info->supports_rpm_write = true;

	return 0;
}