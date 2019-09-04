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
struct switch_ctx {int nr_paths; TYPE_1__* path_list; } ;
struct dm_target {int /*<<< orphan*/  len; struct switch_ctx* private; } ;
typedef  int (* iterate_devices_callout_fn ) (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;
struct TYPE_2__ {int /*<<< orphan*/  start; int /*<<< orphan*/  dmdev; } ;

/* Variables and functions */

__attribute__((used)) static int switch_iterate_devices(struct dm_target *ti,
				  iterate_devices_callout_fn fn, void *data)
{
	struct switch_ctx *sctx = ti->private;
	int path_nr;
	int r;

	for (path_nr = 0; path_nr < sctx->nr_paths; path_nr++) {
		r = fn(ti, sctx->path_list[path_nr].dmdev,
			 sctx->path_list[path_nr].start, ti->len, data);
		if (r)
			return r;
	}

	return 0;
}