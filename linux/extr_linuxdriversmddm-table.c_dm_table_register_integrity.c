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
struct mapped_device {int dummy; } ;
struct gendisk {int /*<<< orphan*/  disk_name; } ;
struct dm_table {int integrity_supported; struct mapped_device* md; scalar_t__ integrity_added; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_get_integrity (struct gendisk*) ; 
 scalar_t__ blk_integrity_compare (int /*<<< orphan*/ ,struct gendisk*) ; 
 int /*<<< orphan*/  blk_integrity_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_device_name (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_disk (struct mapped_device*) ; 
 struct gendisk* dm_table_get_integrity_disk (struct dm_table*) ; 
 int /*<<< orphan*/  integrity_profile_exists (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dm_table_register_integrity(struct dm_table *t)
{
	struct mapped_device *md = t->md;
	struct gendisk *template_disk = NULL;

	/* If target handles integrity itself do not register it here. */
	if (t->integrity_added)
		return 0;

	template_disk = dm_table_get_integrity_disk(t);
	if (!template_disk)
		return 0;

	if (!integrity_profile_exists(dm_disk(md))) {
		t->integrity_supported = true;
		/*
		 * Register integrity profile during table load; we can do
		 * this because the final profile must match during resume.
		 */
		blk_integrity_register(dm_disk(md),
				       blk_get_integrity(template_disk));
		return 0;
	}

	/*
	 * If DM device already has an initialized integrity
	 * profile the new profile should not conflict.
	 */
	if (blk_integrity_compare(dm_disk(md), template_disk) < 0) {
		DMWARN("%s: conflict with existing integrity profile: "
		       "%s profile mismatch",
		       dm_device_name(t->md),
		       template_disk->disk_name);
		return 1;
	}

	/* Preserve existing integrity profile */
	t->integrity_supported = true;
	return 0;
}