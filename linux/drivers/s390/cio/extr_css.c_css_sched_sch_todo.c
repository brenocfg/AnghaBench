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
struct TYPE_2__ {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; } ;
struct subchannel {int todo; int /*<<< orphan*/  dev; int /*<<< orphan*/  todo_work; TYPE_1__ schid; } ;
typedef  enum sch_todo { ____Placeholder_sch_todo } sch_todo ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cio_work_q ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void css_sched_sch_todo(struct subchannel *sch, enum sch_todo todo)
{
	CIO_MSG_EVENT(4, "sch_todo: sched sch=0.%x.%04x todo=%d\n",
		      sch->schid.ssid, sch->schid.sch_no, todo);
	if (sch->todo >= todo)
		return;
	/* Get workqueue ref. */
	if (!get_device(&sch->dev))
		return;
	sch->todo = todo;
	if (!queue_work(cio_work_q, &sch->todo_work)) {
		/* Already queued, release workqueue ref. */
		put_device(&sch->dev);
	}
}