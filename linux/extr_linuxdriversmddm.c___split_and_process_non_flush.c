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
struct dm_target {int dummy; } ;
struct clone_info {unsigned int sector; unsigned int sector_count; int /*<<< orphan*/  map; struct bio* bio; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ REQ_OP_ZONE_REPORT ; 
 int __clone_and_map_data_bio (struct clone_info*,struct dm_target*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  __process_abnormal_io (struct clone_info*,struct dm_target*,int*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 struct dm_target* dm_table_find_target (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dm_target_is_valid (struct dm_target*) ; 
 int /*<<< orphan*/  max_io_len (unsigned int,struct dm_target*) ; 
 unsigned int min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sector_t ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __split_and_process_non_flush(struct clone_info *ci)
{
	struct bio *bio = ci->bio;
	struct dm_target *ti;
	unsigned len;
	int r;

	ti = dm_table_find_target(ci->map, ci->sector);
	if (!dm_target_is_valid(ti))
		return -EIO;

	if (unlikely(__process_abnormal_io(ci, ti, &r)))
		return r;

	if (bio_op(bio) == REQ_OP_ZONE_REPORT)
		len = ci->sector_count;
	else
		len = min_t(sector_t, max_io_len(ci->sector, ti),
			    ci->sector_count);

	r = __clone_and_map_data_bio(ci, ti, ci->sector, &len);
	if (r < 0)
		return r;

	ci->sector += len;
	ci->sector_count -= len;

	return 0;
}