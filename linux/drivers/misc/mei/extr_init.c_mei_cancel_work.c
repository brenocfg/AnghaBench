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
struct mei_device {int /*<<< orphan*/  timer_work; int /*<<< orphan*/  bus_rescan_work; int /*<<< orphan*/  reset_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

void mei_cancel_work(struct mei_device *dev)
{
	cancel_work_sync(&dev->reset_work);
	cancel_work_sync(&dev->bus_rescan_work);

	cancel_delayed_work_sync(&dev->timer_work);
}