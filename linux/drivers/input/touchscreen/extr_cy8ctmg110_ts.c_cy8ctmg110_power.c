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
struct cy8ctmg110 {scalar_t__ reset_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_direction_output (scalar_t__,int) ; 

__attribute__((used)) static void cy8ctmg110_power(struct cy8ctmg110 *ts, bool poweron)
{
	if (ts->reset_pin)
		gpio_direction_output(ts->reset_pin, 1 - poweron);
}