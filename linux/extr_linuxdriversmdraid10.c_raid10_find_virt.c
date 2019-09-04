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
struct geom {int far_set_size; int raid_disks; scalar_t__ chunk_mask; scalar_t__ chunk_shift; int far_copies; int near_copies; scalar_t__ stride; scalar_t__ far_offset; } ;
struct r10conf {struct geom geo; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int sector_div (scalar_t__,int) ; 

__attribute__((used)) static sector_t raid10_find_virt(struct r10conf *conf, sector_t sector, int dev)
{
	sector_t offset, chunk, vchunk;
	/* Never use conf->prev as this is only called during resync
	 * or recovery, so reshape isn't happening
	 */
	struct geom *geo = &conf->geo;
	int far_set_start = (dev / geo->far_set_size) * geo->far_set_size;
	int far_set_size = geo->far_set_size;
	int last_far_set_start;

	if (geo->raid_disks % geo->far_set_size) {
		last_far_set_start = (geo->raid_disks / geo->far_set_size) - 1;
		last_far_set_start *= geo->far_set_size;

		if (dev >= last_far_set_start) {
			far_set_size = geo->far_set_size;
			far_set_size += (geo->raid_disks % geo->far_set_size);
			far_set_start = last_far_set_start;
		}
	}

	offset = sector & geo->chunk_mask;
	if (geo->far_offset) {
		int fc;
		chunk = sector >> geo->chunk_shift;
		fc = sector_div(chunk, geo->far_copies);
		dev -= fc * geo->near_copies;
		if (dev < far_set_start)
			dev += far_set_size;
	} else {
		while (sector >= geo->stride) {
			sector -= geo->stride;
			if (dev < (geo->near_copies + far_set_start))
				dev += far_set_size - geo->near_copies;
			else
				dev -= geo->near_copies;
		}
		chunk = sector >> geo->chunk_shift;
	}
	vchunk = chunk * geo->raid_disks + dev;
	sector_div(vchunk, geo->near_copies);
	return (vchunk << geo->chunk_shift) + offset;
}