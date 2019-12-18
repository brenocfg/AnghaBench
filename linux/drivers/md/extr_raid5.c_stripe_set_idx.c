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
struct stripe_head {int dummy; } ;
struct r5conf {int prev_chunk_sectors; int chunk_sectors; int previous_raid_disks; int raid_disks; int max_degraded; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  raid5_compute_sector (struct r5conf*,int,int,int*,struct stripe_head*) ; 
 int sector_div (int,int) ; 

__attribute__((used)) static void stripe_set_idx(sector_t stripe, struct r5conf *conf, int previous,
			    struct stripe_head *sh)
{
	int sectors_per_chunk =
		previous ? conf->prev_chunk_sectors : conf->chunk_sectors;
	int dd_idx;
	int chunk_offset = sector_div(stripe, sectors_per_chunk);
	int disks = previous ? conf->previous_raid_disks : conf->raid_disks;

	raid5_compute_sector(conf,
			     stripe * (disks - conf->max_degraded)
			     *sectors_per_chunk + chunk_offset,
			     previous,
			     &dd_idx, sh);
}