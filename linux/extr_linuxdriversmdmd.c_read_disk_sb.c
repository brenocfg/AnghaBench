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
struct md_rdev {int sb_loaded; int /*<<< orphan*/  bdev; int /*<<< orphan*/  sb_page; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_page_io (struct md_rdev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_disk_sb(struct md_rdev *rdev, int size)
{
	char b[BDEVNAME_SIZE];

	if (rdev->sb_loaded)
		return 0;

	if (!sync_page_io(rdev, 0, size, rdev->sb_page, REQ_OP_READ, 0, true))
		goto fail;
	rdev->sb_loaded = 1;
	return 0;

fail:
	pr_err("md: disabled device %s, could not read superblock.\n",
	       bdevname(rdev->bdev,b));
	return -EINVAL;
}