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
 int smu10_set_clock_limit (struct pp_hwmgr*,void const*) ; 

__attribute__((used)) static int smu10_set_power_state_tasks(struct pp_hwmgr *hwmgr, const void *input)
{
	return smu10_set_clock_limit(hwmgr, input);
}