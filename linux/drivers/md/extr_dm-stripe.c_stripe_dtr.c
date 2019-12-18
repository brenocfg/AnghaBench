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
struct stripe_c {unsigned int stripes; int /*<<< orphan*/  trigger_event; TYPE_1__* stripe; } ;
struct dm_target {scalar_t__ private; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_put_device (struct dm_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct stripe_c*) ; 

__attribute__((used)) static void stripe_dtr(struct dm_target *ti)
{
	unsigned int i;
	struct stripe_c *sc = (struct stripe_c *) ti->private;

	for (i = 0; i < sc->stripes; i++)
		dm_put_device(ti, sc->stripe[i].dev);

	flush_work(&sc->trigger_event);
	kfree(sc);
}