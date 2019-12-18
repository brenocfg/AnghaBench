#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ file; } ;
struct bitmap {int /*<<< orphan*/  mddev; int /*<<< orphan*/  pending_writes; int /*<<< orphan*/  write_wait; TYPE_1__ storage; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_super_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void md_bitmap_wait_writes(struct bitmap *bitmap)
{
	if (bitmap->storage.file)
		wait_event(bitmap->write_wait,
			   atomic_read(&bitmap->pending_writes)==0);
	else
		/* Note that we ignore the return value.  The writes
		 * might have failed, but that would just mean that
		 * some bits which should be cleared haven't been,
		 * which is safe.  The relevant bitmap blocks will
		 * probably get written again, but there is no great
		 * loss if they aren't.
		 */
		md_super_wait(bitmap->mddev);
}