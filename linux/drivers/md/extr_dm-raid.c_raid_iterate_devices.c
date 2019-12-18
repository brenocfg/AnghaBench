#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int raid_disks; int /*<<< orphan*/  dev_sectors; } ;
struct raid_set {TYPE_1__ md; TYPE_2__* dev; } ;
struct dm_target {struct raid_set* private; } ;
typedef  int (* iterate_devices_callout_fn ) (struct dm_target*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;
struct TYPE_4__ {scalar_t__ data_dev; } ;

/* Variables and functions */

__attribute__((used)) static int raid_iterate_devices(struct dm_target *ti,
				iterate_devices_callout_fn fn, void *data)
{
	struct raid_set *rs = ti->private;
	unsigned int i;
	int r = 0;

	for (i = 0; !r && i < rs->md.raid_disks; i++)
		if (rs->dev[i].data_dev)
			r = fn(ti,
				 rs->dev[i].data_dev,
				 0, /* No offset on data devs */
				 rs->md.dev_sectors,
				 data);

	return r;
}