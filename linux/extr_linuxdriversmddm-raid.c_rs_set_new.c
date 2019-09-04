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
struct mddev {scalar_t__ delta_disks; int /*<<< orphan*/  raid_disks; int /*<<< orphan*/  new_chunk_sectors; int /*<<< orphan*/  chunk_sectors; int /*<<< orphan*/  new_layout; int /*<<< orphan*/  layout; int /*<<< orphan*/  new_level; int /*<<< orphan*/  level; } ;
struct raid_set {int /*<<< orphan*/  raid_disks; struct mddev md; } ;

/* Variables and functions */

__attribute__((used)) static void rs_set_new(struct raid_set *rs)
{
	struct mddev *mddev = &rs->md;

	mddev->level = mddev->new_level;
	mddev->layout = mddev->new_layout;
	mddev->chunk_sectors = mddev->new_chunk_sectors;
	mddev->raid_disks = rs->raid_disks;
	mddev->delta_disks = 0;
}