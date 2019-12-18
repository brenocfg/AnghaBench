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
struct mddev {int layout; int chunk_sectors; int raid_disks; int delta_disks; int new_layout; int new_chunk_sectors; } ;
struct geom {int raid_disks; int near_copies; int far_copies; int far_offset; int far_set_size; int chunk_mask; int /*<<< orphan*/  chunk_shift; } ;
typedef  enum geo_type { ____Placeholder_geo_type } geo_type ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  ffz (int) ; 
#define  geo_new 130 
#define  geo_old 129 
#define  geo_start 128 
 int /*<<< orphan*/  is_power_of_2 (int) ; 

__attribute__((used)) static int setup_geo(struct geom *geo, struct mddev *mddev, enum geo_type new)
{
	int nc, fc, fo;
	int layout, chunk, disks;
	switch (new) {
	case geo_old:
		layout = mddev->layout;
		chunk = mddev->chunk_sectors;
		disks = mddev->raid_disks - mddev->delta_disks;
		break;
	case geo_new:
		layout = mddev->new_layout;
		chunk = mddev->new_chunk_sectors;
		disks = mddev->raid_disks;
		break;
	default: /* avoid 'may be unused' warnings */
	case geo_start: /* new when starting reshape - raid_disks not
			 * updated yet. */
		layout = mddev->new_layout;
		chunk = mddev->new_chunk_sectors;
		disks = mddev->raid_disks + mddev->delta_disks;
		break;
	}
	if (layout >> 19)
		return -1;
	if (chunk < (PAGE_SIZE >> 9) ||
	    !is_power_of_2(chunk))
		return -2;
	nc = layout & 255;
	fc = (layout >> 8) & 255;
	fo = layout & (1<<16);
	geo->raid_disks = disks;
	geo->near_copies = nc;
	geo->far_copies = fc;
	geo->far_offset = fo;
	switch (layout >> 17) {
	case 0:	/* original layout.  simple but not always optimal */
		geo->far_set_size = disks;
		break;
	case 1: /* "improved" layout which was buggy.  Hopefully no-one is
		 * actually using this, but leave code here just in case.*/
		geo->far_set_size = disks/fc;
		WARN(geo->far_set_size < fc,
		     "This RAID10 layout does not provide data safety - please backup and create new array\n");
		break;
	case 2: /* "improved" layout fixed to match documentation */
		geo->far_set_size = fc * nc;
		break;
	default: /* Not a valid layout */
		return -1;
	}
	geo->chunk_mask = chunk - 1;
	geo->chunk_shift = ffz(~chunk);
	return nc*fc;
}