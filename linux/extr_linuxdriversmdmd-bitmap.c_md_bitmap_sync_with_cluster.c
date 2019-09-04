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
struct mddev {struct bitmap* bitmap; } ;
struct bitmap {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  md_bitmap_end_sync (struct bitmap*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_bitmap_start_sync (struct bitmap*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 

void md_bitmap_sync_with_cluster(struct mddev *mddev,
			      sector_t old_lo, sector_t old_hi,
			      sector_t new_lo, sector_t new_hi)
{
	struct bitmap *bitmap = mddev->bitmap;
	sector_t sector, blocks = 0;

	for (sector = old_lo; sector < new_lo; ) {
		md_bitmap_end_sync(bitmap, sector, &blocks, 0);
		sector += blocks;
	}
	WARN((blocks > new_lo) && old_lo, "alignment is not correct for lo\n");

	for (sector = old_hi; sector < new_hi; ) {
		md_bitmap_start_sync(bitmap, sector, &blocks, 0);
		sector += blocks;
	}
	WARN((blocks > new_hi) && old_hi, "alignment is not correct for hi\n");
}