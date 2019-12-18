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
struct dm_target {TYPE_1__* type; int /*<<< orphan*/  discards_supported; int /*<<< orphan*/  num_discard_bios; } ;
struct dm_table {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* iterate_devices ) (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  device_not_discard_capable ; 
 unsigned int dm_table_get_num_targets (struct dm_table*) ; 
 struct dm_target* dm_table_get_target (struct dm_table*,unsigned int) ; 
 scalar_t__ stub1 (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool dm_table_supports_discards(struct dm_table *t)
{
	struct dm_target *ti;
	unsigned i;

	for (i = 0; i < dm_table_get_num_targets(t); i++) {
		ti = dm_table_get_target(t, i);

		if (!ti->num_discard_bios)
			return false;

		/*
		 * Either the target provides discard support (as implied by setting
		 * 'discards_supported') or it relies on _all_ data devices having
		 * discard support.
		 */
		if (!ti->discards_supported &&
		    (!ti->type->iterate_devices ||
		     ti->type->iterate_devices(ti, device_not_discard_capable, NULL)))
			return false;
	}

	return true;
}