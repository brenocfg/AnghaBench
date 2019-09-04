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
 int AI_MAILBOX_POLL_MSG_TIMEDOUT ; 
 int ETIME ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int xgpu_ai_mailbox_rcv_msg (struct amdgpu_device*,int) ; 

__attribute__((used)) static int xgpu_ai_poll_msg(struct amdgpu_device *adev, enum idh_event event)
{
	int r, timeout = AI_MAILBOX_POLL_MSG_TIMEDOUT;

	do {
		r = xgpu_ai_mailbox_rcv_msg(adev, event);
		if (!r)
			return 0;

		msleep(10);
		timeout -= 10;
	} while (timeout > 1);

	pr_err("Doesn't get msg:%d from pf, error=%d\n", event, r);

	return -ETIME;
}