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
struct r1bio {long sectors; scalar_t__ sector; } ;
struct mddev {int /*<<< orphan*/  bitmap; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  md_bitmap_end_sync (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 

__attribute__((used)) static void abort_sync_write(struct mddev *mddev, struct r1bio *r1_bio)
{
	sector_t sync_blocks = 0;
	sector_t s = r1_bio->sector;
	long sectors_to_go = r1_bio->sectors;

	/* make sure these bits don't get cleared. */
	do {
		md_bitmap_end_sync(mddev->bitmap, s, &sync_blocks, 1);
		s += sync_blocks;
		sectors_to_go -= sync_blocks;
	} while (sectors_to_go > 0);
}