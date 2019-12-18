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
struct st1232_ts_data {scalar_t__ reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 

__attribute__((used)) static void st1232_ts_power(struct st1232_ts_data *ts, bool poweron)
{
	if (ts->reset_gpio)
		gpiod_set_value_cansleep(ts->reset_gpio, !poweron);
}