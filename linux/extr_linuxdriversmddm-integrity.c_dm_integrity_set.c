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
struct gendisk {int /*<<< orphan*/  queue; } ;
struct dm_target {int /*<<< orphan*/  table; } ;
struct dm_integrity_c {TYPE_1__* sb; int /*<<< orphan*/  tag_size; } ;
struct blk_integrity {scalar_t__ interval_exp; int /*<<< orphan*/  tuple_size; int /*<<< orphan*/  tag_size; int /*<<< orphan*/ * profile; } ;
typedef  int /*<<< orphan*/  bi ;
struct TYPE_2__ {scalar_t__ log2_sectors_per_block; } ;

/* Variables and functions */
 scalar_t__ SECTOR_SHIFT ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  blk_integrity_register (struct gendisk*,struct blk_integrity*) ; 
 int /*<<< orphan*/  blk_queue_max_integrity_segments (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gendisk* dm_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_integrity_profile ; 
 int /*<<< orphan*/  dm_table_get_md (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct blk_integrity*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dm_integrity_set(struct dm_target *ti, struct dm_integrity_c *ic)
{
	struct gendisk *disk = dm_disk(dm_table_get_md(ti->table));
	struct blk_integrity bi;

	memset(&bi, 0, sizeof(bi));
	bi.profile = &dm_integrity_profile;
	bi.tuple_size = ic->tag_size;
	bi.tag_size = bi.tuple_size;
	bi.interval_exp = ic->sb->log2_sectors_per_block + SECTOR_SHIFT;

	blk_integrity_register(disk, &bi);
	blk_queue_max_integrity_segments(disk->queue, UINT_MAX);
}