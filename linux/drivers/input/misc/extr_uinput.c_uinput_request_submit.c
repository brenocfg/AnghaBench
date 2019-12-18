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
struct uinput_request {int retval; int /*<<< orphan*/  id; int /*<<< orphan*/  done; } ;
struct uinput_device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  uinput_request_release_slot (struct uinput_device*,int /*<<< orphan*/ ) ; 
 int uinput_request_reserve_slot (struct uinput_device*,struct uinput_request*) ; 
 int uinput_request_send (struct uinput_device*,struct uinput_request*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int uinput_request_submit(struct uinput_device *udev,
				 struct uinput_request *request)
{
	int retval;

	retval = uinput_request_reserve_slot(udev, request);
	if (retval)
		return retval;

	retval = uinput_request_send(udev, request);
	if (retval)
		goto out;

	if (!wait_for_completion_timeout(&request->done, 30 * HZ)) {
		retval = -ETIMEDOUT;
		goto out;
	}

	retval = request->retval;

 out:
	uinput_request_release_slot(udev, request->id);
	return retval;
}