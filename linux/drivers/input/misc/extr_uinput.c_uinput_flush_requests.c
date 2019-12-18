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
struct uinput_request {int /*<<< orphan*/  done; int /*<<< orphan*/  retval; } ;
struct uinput_device {int /*<<< orphan*/  requests_lock; struct uinput_request** requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int UINPUT_NUM_REQUESTS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uinput_flush_requests(struct uinput_device *udev)
{
	struct uinput_request *request;
	int i;

	spin_lock(&udev->requests_lock);

	for (i = 0; i < UINPUT_NUM_REQUESTS; i++) {
		request = udev->requests[i];
		if (request) {
			request->retval = -ENODEV;
			complete(&request->done);
		}
	}

	spin_unlock(&udev->requests_lock);
}