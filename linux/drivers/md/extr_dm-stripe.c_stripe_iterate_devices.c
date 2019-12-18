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
struct stripe_c {unsigned int stripes; int /*<<< orphan*/  stripe_width; TYPE_1__* stripe; } ;
struct dm_target {struct stripe_c* private; } ;
typedef  int (* iterate_devices_callout_fn ) (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;
struct TYPE_2__ {int /*<<< orphan*/  physical_start; int /*<<< orphan*/  dev; } ;

/* Variables and functions */

__attribute__((used)) static int stripe_iterate_devices(struct dm_target *ti,
				  iterate_devices_callout_fn fn, void *data)
{
	struct stripe_c *sc = ti->private;
	int ret = 0;
	unsigned i = 0;

	do {
		ret = fn(ti, sc->stripe[i].dev,
			 sc->stripe[i].physical_start,
			 sc->stripe_width, data);
	} while (!ret && ++i < sc->stripes);

	return ret;
}