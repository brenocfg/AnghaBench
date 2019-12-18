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
struct ad5758_state {scalar_t__ gpio_reset; } ;

/* Variables and functions */
 int ad5758_soft_reset (struct ad5758_state*) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ad5758_reset(struct ad5758_state *st)
{
	if (st->gpio_reset) {
		gpiod_set_value(st->gpio_reset, 0);
		usleep_range(100, 1000);
		gpiod_set_value(st->gpio_reset, 1);
		usleep_range(100, 1000);

		return 0;
	} else {
		/* Perform a software reset */
		return ad5758_soft_reset(st);
	}
}