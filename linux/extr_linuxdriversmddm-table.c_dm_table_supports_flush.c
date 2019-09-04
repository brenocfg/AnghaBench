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
struct dm_target {TYPE_1__* type; scalar_t__ flush_supported; int /*<<< orphan*/  num_flush_bios; } ;
struct dm_table {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* iterate_devices ) (struct dm_target*,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  device_flush_capable ; 
 unsigned int dm_table_get_num_targets (struct dm_table*) ; 
 struct dm_target* dm_table_get_target (struct dm_table*,unsigned int) ; 
 scalar_t__ stub1 (struct dm_target*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static bool dm_table_supports_flush(struct dm_table *t, unsigned long flush)
{
	struct dm_target *ti;
	unsigned i;

	/*
	 * Require at least one underlying device to support flushes.
	 * t->devices includes internal dm devices such as mirror logs
	 * so we need to use iterate_devices here, which targets
	 * supporting flushes must provide.
	 */
	for (i = 0; i < dm_table_get_num_targets(t); i++) {
		ti = dm_table_get_target(t, i);

		if (!ti->num_flush_bios)
			continue;

		if (ti->flush_supported)
			return true;

		if (ti->type->iterate_devices &&
		    ti->type->iterate_devices(ti, device_flush_capable, (void *) flush))
			return true;
	}

	return false;
}