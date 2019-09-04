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
struct uhid_device {int running; int /*<<< orphan*/  rd_data; int /*<<< orphan*/  hid; int /*<<< orphan*/  worker; int /*<<< orphan*/  report_wait; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_destroy_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uhid_dev_destroy(struct uhid_device *uhid)
{
	if (!uhid->running)
		return -EINVAL;

	uhid->running = false;
	wake_up_interruptible(&uhid->report_wait);

	cancel_work_sync(&uhid->worker);

	hid_destroy_device(uhid->hid);
	kfree(uhid->rd_data);

	return 0;
}