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
struct era {int /*<<< orphan*/  origin_dev; } ;
struct dm_target {struct era* private; } ;
typedef  int (* iterate_devices_callout_fn ) (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  get_dev_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int era_iterate_devices(struct dm_target *ti,
			       iterate_devices_callout_fn fn, void *data)
{
	struct era *era = ti->private;
	return fn(ti, era->origin_dev, 0, get_dev_size(era->origin_dev), data);
}