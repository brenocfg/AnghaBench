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
struct TYPE_2__ {scalar_t__ cmd; int /*<<< orphan*/  ready; } ;
struct wiimote_data {TYPE_1__ state; } ;

/* Variables and functions */
 int EIO ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  HZ ; 
 scalar_t__ WIIPROTO_REQ_NULL ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int wiimote_cmd_wait(struct wiimote_data *wdata)
{
	int ret;

	/* The completion acts as implicit memory barrier so we can safely
	 * assume that state.cmd is set on success/failure and isn't accessed
	 * by any other thread, anymore. */

	ret = wait_for_completion_interruptible_timeout(&wdata->state.ready, HZ);
	if (ret < 0)
		return -ERESTARTSYS;
	else if (ret == 0)
		return -EIO;
	else if (wdata->state.cmd != WIIPROTO_REQ_NULL)
		return -EIO;
	else
		return 0;
}