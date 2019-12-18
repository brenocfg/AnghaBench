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
struct hl_device {int late_init_done; TYPE_1__* asic_funcs; int /*<<< orphan*/  work_heartbeat; scalar_t__ heartbeat; int /*<<< orphan*/  work_freq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* late_fini ) (struct hl_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*) ; 

__attribute__((used)) static void device_late_fini(struct hl_device *hdev)
{
	if (!hdev->late_init_done)
		return;

	cancel_delayed_work_sync(&hdev->work_freq);
	if (hdev->heartbeat)
		cancel_delayed_work_sync(&hdev->work_heartbeat);

	if (hdev->asic_funcs->late_fini)
		hdev->asic_funcs->late_fini(hdev);

	hdev->late_init_done = false;
}