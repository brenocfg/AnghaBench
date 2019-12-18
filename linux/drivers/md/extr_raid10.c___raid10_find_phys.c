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
struct r10bio {int sector; TYPE_1__* devs; } ;
struct geom {int raid_disks; int far_set_size; int chunk_shift; int chunk_mask; int near_copies; int far_copies; scalar_t__ stride; scalar_t__ far_offset; } ;
typedef  int sector_t ;
struct TYPE_2__ {int devnum; int addr; } ;

/* Variables and functions */
 int sector_div (int,int) ; 

__attribute__((used)) static void __raid10_find_phys(struct geom *geo, struct r10bio *r10bio)
{
	int n,f;
	sector_t sector;
	sector_t chunk;
	sector_t stripe;
	int dev;
	int slot = 0;
	int last_far_set_start, last_far_set_size;

	last_far_set_start = (geo->raid_disks / geo->far_set_size) - 1;
	last_far_set_start *= geo->far_set_size;

	last_far_set_size = geo->far_set_size;
	last_far_set_size += (geo->raid_disks % geo->far_set_size);

	/* now calculate first sector/dev */
	chunk = r10bio->sector >> geo->chunk_shift;
	sector = r10bio->sector & geo->chunk_mask;

	chunk *= geo->near_copies;
	stripe = chunk;
	dev = sector_div(stripe, geo->raid_disks);
	if (geo->far_offset)
		stripe *= geo->far_copies;

	sector += stripe << geo->chunk_shift;

	/* and calculate all the others */
	for (n = 0; n < geo->near_copies; n++) {
		int d = dev;
		int set;
		sector_t s = sector;
		r10bio->devs[slot].devnum = d;
		r10bio->devs[slot].addr = s;
		slot++;

		for (f = 1; f < geo->far_copies; f++) {
			set = d / geo->far_set_size;
			d += geo->near_copies;

			if ((geo->raid_disks % geo->far_set_size) &&
			    (d > last_far_set_start)) {
				d -= last_far_set_start;
				d %= last_far_set_size;
				d += last_far_set_start;
			} else {
				d %= geo->far_set_size;
				d += geo->far_set_size * set;
			}
			s += geo->stride;
			r10bio->devs[slot].devnum = d;
			r10bio->devs[slot].addr = s;
			slot++;
		}
		dev++;
		if (dev >= geo->raid_disks) {
			dev = 0;
			sector += (geo->chunk_mask + 1);
		}
	}
}