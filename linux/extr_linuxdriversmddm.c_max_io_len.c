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
struct dm_target {int max_io_len; } ;
typedef  int sector_t ;

/* Variables and functions */
 int dm_target_offset (struct dm_target*,int) ; 
 int max_io_len_target_boundary (int,struct dm_target*) ; 
 int sector_div (int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static sector_t max_io_len(sector_t sector, struct dm_target *ti)
{
	sector_t len = max_io_len_target_boundary(sector, ti);
	sector_t offset, max_len;

	/*
	 * Does the target need to split even further?
	 */
	if (ti->max_io_len) {
		offset = dm_target_offset(ti, sector);
		if (unlikely(ti->max_io_len & (ti->max_io_len - 1)))
			max_len = sector_div(offset, ti->max_io_len);
		else
			max_len = offset & (ti->max_io_len - 1);
		max_len = ti->max_io_len - max_len;

		if (len > max_len)
			len = max_len;
	}

	return len;
}