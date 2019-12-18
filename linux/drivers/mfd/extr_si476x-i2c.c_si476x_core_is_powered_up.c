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
struct si476x_core {scalar_t__ power_state; } ;

/* Variables and functions */
 scalar_t__ SI476X_POWER_UP_FULL ; 

bool si476x_core_is_powered_up(struct si476x_core *core)
{
	return core->power_state == SI476X_POWER_UP_FULL;
}