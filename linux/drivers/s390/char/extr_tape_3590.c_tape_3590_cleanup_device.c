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
struct tape_device {int /*<<< orphan*/ * discdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tape_3590_wq ; 
 int /*<<< orphan*/  tape_std_unassign (struct tape_device*) ; 

__attribute__((used)) static void
tape_3590_cleanup_device(struct tape_device *device)
{
	flush_workqueue(tape_3590_wq);
	tape_std_unassign(device);

	kfree(device->discdata);
	device->discdata = NULL;
}