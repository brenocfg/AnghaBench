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
struct hl_device {int in_debug; int /*<<< orphan*/  debug_lock; int /*<<< orphan*/  dev; TYPE_1__* asic_funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* halt_coresight ) (struct hl_device*) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*) ; 

int hl_device_set_debug_mode(struct hl_device *hdev, bool enable)
{
	int rc = 0;

	mutex_lock(&hdev->debug_lock);

	if (!enable) {
		if (!hdev->in_debug) {
			dev_err(hdev->dev,
				"Failed to disable debug mode because device was not in debug mode\n");
			rc = -EFAULT;
			goto out;
		}

		hdev->asic_funcs->halt_coresight(hdev);
		hdev->in_debug = 0;

		goto out;
	}

	if (hdev->in_debug) {
		dev_err(hdev->dev,
			"Failed to enable debug mode because device is already in debug mode\n");
		rc = -EFAULT;
		goto out;
	}

	hdev->in_debug = 1;

out:
	mutex_unlock(&hdev->debug_lock);

	return rc;
}