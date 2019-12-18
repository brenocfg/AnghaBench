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
struct hid_device {int /*<<< orphan*/  ll_open_lock; TYPE_1__* ll_driver; int /*<<< orphan*/  ll_open_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct hid_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hid_device*) ; 

void hid_hw_close(struct hid_device *hdev)
{
	mutex_lock(&hdev->ll_open_lock);
	if (!--hdev->ll_open_count)
		hdev->ll_driver->close(hdev);
	mutex_unlock(&hdev->ll_open_lock);
}