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
struct dm_target {TYPE_1__* type; } ;
struct dm_table {int dummy; } ;
typedef  int /*<<< orphan*/  iterate_devices_callout_fn ;
struct TYPE_2__ {int /*<<< orphan*/  (* iterate_devices ) (struct dm_target*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  direct_access; } ;

/* Variables and functions */
 unsigned int dm_table_get_num_targets (struct dm_table*) ; 
 struct dm_target* dm_table_get_target (struct dm_table*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct dm_target*,int /*<<< orphan*/ ,int*) ; 

bool dm_table_supports_dax(struct dm_table *t,
			   iterate_devices_callout_fn iterate_fn, int *blocksize)
{
	struct dm_target *ti;
	unsigned i;

	/* Ensure that all targets support DAX. */
	for (i = 0; i < dm_table_get_num_targets(t); i++) {
		ti = dm_table_get_target(t, i);

		if (!ti->type->direct_access)
			return false;

		if (!ti->type->iterate_devices ||
		    !ti->type->iterate_devices(ti, iterate_fn, blocksize))
			return false;
	}

	return true;
}