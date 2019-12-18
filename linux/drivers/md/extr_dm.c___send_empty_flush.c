#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dm_target {int /*<<< orphan*/  num_flush_bios; } ;
struct clone_info {int /*<<< orphan*/  bio; int /*<<< orphan*/  map; TYPE_2__* io; } ;
struct TYPE_4__ {TYPE_1__* md; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __send_duplicate_bios (struct clone_info*,struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_disassociate_blkg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_has_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dm_target* dm_table_get_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __send_empty_flush(struct clone_info *ci)
{
	unsigned target_nr = 0;
	struct dm_target *ti;

	/*
	 * Empty flush uses a statically initialized bio, as the base for
	 * cloning.  However, blkg association requires that a bdev is
	 * associated with a gendisk, which doesn't happen until the bdev is
	 * opened.  So, blkg association is done at issue time of the flush
	 * rather than when the device is created in alloc_dev().
	 */
	bio_set_dev(ci->bio, ci->io->md->bdev);

	BUG_ON(bio_has_data(ci->bio));
	while ((ti = dm_table_get_target(ci->map, target_nr++)))
		__send_duplicate_bios(ci, ti, ti->num_flush_bios, NULL);

	bio_disassociate_blkg(ci->bio);

	return 0;
}