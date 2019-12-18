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
struct md_rdev {int /*<<< orphan*/  badblocks; int /*<<< orphan*/ * bb_page; scalar_t__ sectors; scalar_t__ sb_start; int /*<<< orphan*/ * sb_page; scalar_t__ sb_loaded; } ;

/* Variables and functions */
 int /*<<< orphan*/  badblocks_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 

void md_rdev_clear(struct md_rdev *rdev)
{
	if (rdev->sb_page) {
		put_page(rdev->sb_page);
		rdev->sb_loaded = 0;
		rdev->sb_page = NULL;
		rdev->sb_start = 0;
		rdev->sectors = 0;
	}
	if (rdev->bb_page) {
		put_page(rdev->bb_page);
		rdev->bb_page = NULL;
	}
	badblocks_exit(&rdev->badblocks);
}