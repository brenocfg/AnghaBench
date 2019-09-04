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
struct uinput_device {int /*<<< orphan*/  requests_waitq; int /*<<< orphan*/  requests_lock; int /*<<< orphan*/ ** requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uinput_request_release_slot(struct uinput_device *udev,
					unsigned int id)
{
	/* Mark slot as available */
	spin_lock(&udev->requests_lock);
	udev->requests[id] = NULL;
	spin_unlock(&udev->requests_lock);

	wake_up(&udev->requests_waitq);
}