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
struct dm_target {int /*<<< orphan*/  len; struct dm_origin* private; } ;
struct dm_origin {int /*<<< orphan*/  dev; } ;
typedef  int (* iterate_devices_callout_fn ) (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */

__attribute__((used)) static int origin_iterate_devices(struct dm_target *ti,
				  iterate_devices_callout_fn fn, void *data)
{
	struct dm_origin *o = ti->private;

	return fn(ti, o->dev, 0, ti->len, data);
}