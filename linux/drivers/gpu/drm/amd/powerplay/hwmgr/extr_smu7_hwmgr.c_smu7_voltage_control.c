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
struct smu7_hwmgr {scalar_t__ voltage_control; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
 scalar_t__ SMU7_VOLTAGE_CONTROL_NONE ; 

__attribute__((used)) static bool smu7_voltage_control(const struct pp_hwmgr *hwmgr)
{
	const struct smu7_hwmgr *data =
			(const struct smu7_hwmgr *)(hwmgr->backend);

	return (SMU7_VOLTAGE_CONTROL_NONE != data->voltage_control);
}