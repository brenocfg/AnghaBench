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
struct amdgpu_device {int dummy; } ;
typedef  enum idh_event { ____Placeholder_idh_event } idh_event ;

/* Variables and functions */
 int ETIME ; 
 int VI_MAILBOX_TIMEDOUT ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int xgpu_vi_mailbox_rcv_msg (struct amdgpu_device*,int) ; 

__attribute__((used)) static int xgpu_vi_poll_msg(struct amdgpu_device *adev, enum idh_event event)
{
	int r = 0, timeout = VI_MAILBOX_TIMEDOUT;

	r = xgpu_vi_mailbox_rcv_msg(adev, event);
	while (r) {
		if (timeout <= 0) {
			pr_err("Doesn't get ack from pf.\n");
			r = -ETIME;
			break;
		}
		mdelay(5);
		timeout -= 5;

		r = xgpu_vi_mailbox_rcv_msg(adev, event);
	}

	return r;
}