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
struct TYPE_4__ {int raid_disks; int near_copies; } ;
struct r10conf {scalar_t__ cluster_sync_low; scalar_t__ cluster_sync_high; TYPE_1__* mddev; TYPE_2__ geo; } ;
typedef  int sector_t ;
struct TYPE_3__ {int chunk_sectors; } ;

/* Variables and functions */
 int CLUSTER_RESYNC_WINDOW_SECTORS ; 

__attribute__((used)) static void raid10_set_cluster_sync_high(struct r10conf *conf)
{
	sector_t window_size;
	int extra_chunk, chunks;

	/*
	 * First, here we define "stripe" as a unit which across
	 * all member devices one time, so we get chunks by use
	 * raid_disks / near_copies. Otherwise, if near_copies is
	 * close to raid_disks, then resync window could increases
	 * linearly with the increase of raid_disks, which means
	 * we will suspend a really large IO window while it is not
	 * necessary. If raid_disks is not divisible by near_copies,
	 * an extra chunk is needed to ensure the whole "stripe" is
	 * covered.
	 */

	chunks = conf->geo.raid_disks / conf->geo.near_copies;
	if (conf->geo.raid_disks % conf->geo.near_copies == 0)
		extra_chunk = 0;
	else
		extra_chunk = 1;
	window_size = (chunks + extra_chunk) * conf->mddev->chunk_sectors;

	/*
	 * At least use a 32M window to align with raid1's resync window
	 */
	window_size = (CLUSTER_RESYNC_WINDOW_SECTORS > window_size) ?
			CLUSTER_RESYNC_WINDOW_SECTORS : window_size;

	conf->cluster_sync_high = conf->cluster_sync_low + window_size;
}