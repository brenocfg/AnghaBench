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
typedef  int suspend_state_t ;
struct TYPE_2__ {int mode; int suspend_mode; int standby_mode; } ;

/* Variables and functions */
#define  PM_SUSPEND_MEM 129 
#define  PM_SUSPEND_STANDBY 128 
 int at91_pm_config_ws (int,int) ; 
 TYPE_1__ pm_data ; 

__attribute__((used)) static int at91_pm_begin(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_MEM:
		pm_data.mode = pm_data.suspend_mode;
		break;

	case PM_SUSPEND_STANDBY:
		pm_data.mode = pm_data.standby_mode;
		break;

	default:
		pm_data.mode = -1;
	}

	return at91_pm_config_ws(pm_data.mode, true);
}