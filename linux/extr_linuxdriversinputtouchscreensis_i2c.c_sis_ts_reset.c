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
struct sis_ts_data {scalar_t__ reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void sis_ts_reset(struct sis_ts_data *ts)
{
	if (ts->reset_gpio) {
		/* Get out of reset */
		usleep_range(1000, 2000);
		gpiod_set_value(ts->reset_gpio, 1);
		usleep_range(1000, 2000);
		gpiod_set_value(ts->reset_gpio, 0);
		msleep(100);
	}
}