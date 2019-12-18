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
struct gendisk {int dummy; } ;
struct dm_table {int /*<<< orphan*/  md; scalar_t__ integrity_supported; scalar_t__ integrity_added; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_integrity_compare (int /*<<< orphan*/ ,struct gendisk*) ; 
 int /*<<< orphan*/  blk_integrity_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_device_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_disk (int /*<<< orphan*/ ) ; 
 struct gendisk* dm_table_get_integrity_disk (struct dm_table*) ; 
 scalar_t__ integrity_profile_exists (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_table_verify_integrity(struct dm_table *t)
{
	struct gendisk *template_disk = NULL;

	if (t->integrity_added)
		return;

	if (t->integrity_supported) {
		/*
		 * Verify that the original integrity profile
		 * matches all the devices in this table.
		 */
		template_disk = dm_table_get_integrity_disk(t);
		if (template_disk &&
		    blk_integrity_compare(dm_disk(t->md), template_disk) >= 0)
			return;
	}

	if (integrity_profile_exists(dm_disk(t->md))) {
		DMWARN("%s: unable to establish an integrity profile",
		       dm_device_name(t->md));
		blk_integrity_unregister(dm_disk(t->md));
	}
}