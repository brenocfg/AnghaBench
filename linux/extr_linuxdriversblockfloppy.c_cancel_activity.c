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

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * do_floppy ; 
 int /*<<< orphan*/  fd_timer ; 
 int /*<<< orphan*/  floppy_work ; 

__attribute__((used)) static void cancel_activity(void)
{
	do_floppy = NULL;
	cancel_delayed_work_sync(&fd_timer);
	cancel_work_sync(&floppy_work);
}