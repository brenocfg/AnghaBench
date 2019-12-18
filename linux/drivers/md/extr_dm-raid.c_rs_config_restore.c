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
struct rs_layout {int /*<<< orphan*/  new_chunk_sectors; int /*<<< orphan*/  new_layout; int /*<<< orphan*/  new_level; } ;
struct mddev {int /*<<< orphan*/  new_chunk_sectors; int /*<<< orphan*/  new_layout; int /*<<< orphan*/  new_level; } ;
struct raid_set {struct mddev md; } ;

/* Variables and functions */

__attribute__((used)) static void rs_config_restore(struct raid_set *rs, struct rs_layout *l)
{
	struct mddev *mddev = &rs->md;

	mddev->new_level = l->new_level;
	mddev->new_layout = l->new_layout;
	mddev->new_chunk_sectors = l->new_chunk_sectors;
}