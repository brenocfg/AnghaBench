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
struct TYPE_2__ {unsigned int tier; unsigned int twer; } ;
struct omap_dm_timer {TYPE_1__ context; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __omap_dm_timer_int_enable (struct omap_dm_timer*,unsigned int) ; 
 int /*<<< orphan*/  omap_dm_timer_disable (struct omap_dm_timer*) ; 
 int /*<<< orphan*/  omap_dm_timer_enable (struct omap_dm_timer*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int omap_dm_timer_set_int_enable(struct omap_dm_timer *timer,
					unsigned int value)
{
	if (unlikely(!timer))
		return -EINVAL;

	omap_dm_timer_enable(timer);
	__omap_dm_timer_int_enable(timer, value);

	/* Save the context */
	timer->context.tier = value;
	timer->context.twer = value;
	omap_dm_timer_disable(timer);
	return 0;
}