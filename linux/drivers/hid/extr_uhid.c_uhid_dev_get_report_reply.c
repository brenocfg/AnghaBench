#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ get_report_reply; } ;
struct uhid_event {TYPE_2__ u; } ;
struct uhid_device {int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  uhid_report_wake_up (struct uhid_device*,int /*<<< orphan*/ ,struct uhid_event*) ; 

__attribute__((used)) static int uhid_dev_get_report_reply(struct uhid_device *uhid,
				     struct uhid_event *ev)
{
	if (!uhid->running)
		return -EINVAL;

	uhid_report_wake_up(uhid, ev->u.get_report_reply.id, ev);
	return 0;
}