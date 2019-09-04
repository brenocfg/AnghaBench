#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dm_target {int /*<<< orphan*/  len; struct dm_snapshot* private; } ;
struct dm_snapshot {TYPE_1__* cow; TYPE_1__* origin; } ;
typedef  int (* iterate_devices_callout_fn ) (struct dm_target*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_dev_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snapshot_iterate_devices(struct dm_target *ti,
				    iterate_devices_callout_fn fn, void *data)
{
	struct dm_snapshot *snap = ti->private;
	int r;

	r = fn(ti, snap->origin, 0, ti->len, data);

	if (!r)
		r = fn(ti, snap->cow, 0, get_dev_size(snap->cow->bdev), data);

	return r;
}