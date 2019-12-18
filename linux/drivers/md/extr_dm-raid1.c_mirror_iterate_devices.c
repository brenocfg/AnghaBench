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
struct mirror_set {unsigned int nr_mirrors; TYPE_1__* mirror; } ;
struct dm_target {int /*<<< orphan*/  len; struct mirror_set* private; } ;
typedef  int (* iterate_devices_callout_fn ) (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;
struct TYPE_2__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  dev; } ;

/* Variables and functions */

__attribute__((used)) static int mirror_iterate_devices(struct dm_target *ti,
				  iterate_devices_callout_fn fn, void *data)
{
	struct mirror_set *ms = ti->private;
	int ret = 0;
	unsigned i;

	for (i = 0; !ret && i < ms->nr_mirrors; i++)
		ret = fn(ti, ms->mirror[i].dev,
			 ms->mirror[i].offset, ti->len, data);

	return ret;
}