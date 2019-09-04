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

/* Variables and functions */
 int /*<<< orphan*/  PHM_AutoThrottleSource_Thermal ; 
 int smu7_disable_auto_throttle_source (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_disable_thermal_auto_throttle(struct pp_hwmgr *hwmgr)
{
	return smu7_disable_auto_throttle_source(hwmgr, PHM_AutoThrottleSource_Thermal);
}