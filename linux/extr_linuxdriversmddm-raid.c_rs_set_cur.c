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
struct mddev {int /*<<< orphan*/  chunk_sectors; int /*<<< orphan*/  new_chunk_sectors; int /*<<< orphan*/  layout; int /*<<< orphan*/  new_layout; int /*<<< orphan*/  level; int /*<<< orphan*/  new_level; } ;
struct raid_set {struct mddev md; } ;

/* Variables and functions */

__attribute__((used)) static void rs_set_cur(struct raid_set *rs)
{
	struct mddev *mddev = &rs->md;

	mddev->new_level = mddev->level;
	mddev->new_layout = mddev->layout;
	mddev->new_chunk_sectors = mddev->chunk_sectors;
}