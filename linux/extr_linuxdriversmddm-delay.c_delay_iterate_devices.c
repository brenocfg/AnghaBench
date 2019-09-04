#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dm_target {int /*<<< orphan*/  len; struct delay_c* private; } ;
struct TYPE_6__ {int /*<<< orphan*/  start; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  start; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; int /*<<< orphan*/  dev; } ;
struct delay_c {TYPE_3__ flush; TYPE_2__ write; TYPE_1__ read; } ;
typedef  int (* iterate_devices_callout_fn ) (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */

__attribute__((used)) static int delay_iterate_devices(struct dm_target *ti,
				 iterate_devices_callout_fn fn, void *data)
{
	struct delay_c *dc = ti->private;
	int ret = 0;

	ret = fn(ti, dc->read.dev, dc->read.start, ti->len, data);
	if (ret)
		goto out;
	ret = fn(ti, dc->write.dev, dc->write.start, ti->len, data);
	if (ret)
		goto out;
	ret = fn(ti, dc->flush.dev, dc->flush.start, ti->len, data);
	if (ret)
		goto out;

out:
	return ret;
}