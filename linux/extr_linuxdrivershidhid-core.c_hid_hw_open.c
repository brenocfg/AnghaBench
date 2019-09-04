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
struct hid_device {int /*<<< orphan*/  ll_open_lock; int /*<<< orphan*/  ll_open_count; TYPE_1__* ll_driver; } ;
struct TYPE_2__ {int (* open ) (struct hid_device*) ;} ;

/* Variables and functions */
 int mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct hid_device*) ; 

int hid_hw_open(struct hid_device *hdev)
{
	int ret;

	ret = mutex_lock_killable(&hdev->ll_open_lock);
	if (ret)
		return ret;

	if (!hdev->ll_open_count++) {
		ret = hdev->ll_driver->open(hdev);
		if (ret)
			hdev->ll_open_count--;
	}

	mutex_unlock(&hdev->ll_open_lock);
	return ret;
}