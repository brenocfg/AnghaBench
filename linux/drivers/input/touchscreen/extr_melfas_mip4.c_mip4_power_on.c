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
struct mip4_ts {scalar_t__ gpio_ce; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mip4_power_on(struct mip4_ts *ts)
{
	if (ts->gpio_ce) {
		gpiod_set_value_cansleep(ts->gpio_ce, 1);

		/* Booting delay : 200~300ms */
		usleep_range(200 * 1000, 300 * 1000);
	}

	return 0;
}