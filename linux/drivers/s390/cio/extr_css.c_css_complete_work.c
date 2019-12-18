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

/* Variables and functions */
 int EINTR ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int bus_for_each_drv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cio_work_q ; 
 int /*<<< orphan*/  css_bus_type ; 
 int /*<<< orphan*/  css_eval_scheduled ; 
 int /*<<< orphan*/  css_eval_wq ; 
 int /*<<< orphan*/  css_settle ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int css_complete_work(void)
{
	int ret;

	/* Wait for the evaluation of subchannels to finish. */
	ret = wait_event_interruptible(css_eval_wq,
				       atomic_read(&css_eval_scheduled) == 0);
	if (ret)
		return -EINTR;
	flush_workqueue(cio_work_q);
	/* Wait for the subchannel type specific initialization to finish */
	return bus_for_each_drv(&css_bus_type, NULL, NULL, css_settle);
}