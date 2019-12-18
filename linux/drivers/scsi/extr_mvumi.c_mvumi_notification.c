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
typedef  scalar_t__ u8 ;
struct mvumi_hba {TYPE_1__* pdev; } ;
struct mvumi_event_req {int count; struct mvumi_driver_event* events; } ;
struct mvumi_driver_event {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ APICDB1_EVENT_GETEVENT ; 
 scalar_t__ APICDB1_HOST_GETEVENT ; 
 int MAX_EVENTS_RETURNED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  mvumi_proc_msg (struct mvumi_hba*,void*) ; 
 int /*<<< orphan*/  mvumi_show_event (struct mvumi_hba*,struct mvumi_driver_event*) ; 

__attribute__((used)) static void mvumi_notification(struct mvumi_hba *mhba, u8 msg, void *buffer)
{
	if (msg == APICDB1_EVENT_GETEVENT) {
		int i, count;
		struct mvumi_driver_event *param = NULL;
		struct mvumi_event_req *er = buffer;
		count = er->count;
		if (count > MAX_EVENTS_RETURNED) {
			dev_err(&mhba->pdev->dev, "event count[0x%x] is bigger"
					" than max event count[0x%x].\n",
					count, MAX_EVENTS_RETURNED);
			return;
		}
		for (i = 0; i < count; i++) {
			param = &er->events[i];
			mvumi_show_event(mhba, param);
		}
	} else if (msg == APICDB1_HOST_GETEVENT) {
		mvumi_proc_msg(mhba, buffer);
	}
}