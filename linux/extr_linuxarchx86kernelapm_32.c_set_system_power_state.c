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
typedef  int /*<<< orphan*/  u_short ;

/* Variables and functions */
 int /*<<< orphan*/  APM_DEVICE_ALL ; 
 int set_power_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_system_power_state(u_short state)
{
	return set_power_state(APM_DEVICE_ALL, state);
}