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
struct bitmap {int /*<<< orphan*/  behind_writes; int /*<<< orphan*/  behind_wait; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void md_bitmap_wait_behind_writes(struct mddev *mddev)
{
	struct bitmap *bitmap = mddev->bitmap;

	/* wait for behind writes to complete */
	if (bitmap && atomic_read(&bitmap->behind_writes) > 0) {
		pr_debug("md:%s: behind writes in progress - waiting to stop.\n",
			 mdname(mddev));
		/* need to kick something here to make sure I/O goes? */
		wait_event(bitmap->behind_wait,
			   atomic_read(&bitmap->behind_writes) == 0);
	}
}