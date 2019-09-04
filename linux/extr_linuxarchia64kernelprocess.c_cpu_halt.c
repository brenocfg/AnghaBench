#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long power_consumption; scalar_t__ im; } ;
struct TYPE_5__ {TYPE_1__ pal_power_mgmt_info_s; } ;
typedef  TYPE_2__ pal_power_mgmt_info_u_t ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_pal_halt (int) ; 
 scalar_t__ ia64_pal_halt_info (TYPE_2__*) ; 

void
cpu_halt (void)
{
	pal_power_mgmt_info_u_t power_info[8];
	unsigned long min_power;
	int i, min_power_state;

	if (ia64_pal_halt_info(power_info) != 0)
		return;

	min_power_state = 0;
	min_power = power_info[0].pal_power_mgmt_info_s.power_consumption;
	for (i = 1; i < 8; ++i)
		if (power_info[i].pal_power_mgmt_info_s.im
		    && power_info[i].pal_power_mgmt_info_s.power_consumption < min_power) {
			min_power = power_info[i].pal_power_mgmt_info_s.power_consumption;
			min_power_state = i;
		}

	while (1)
		ia64_pal_halt(min_power_state);
}