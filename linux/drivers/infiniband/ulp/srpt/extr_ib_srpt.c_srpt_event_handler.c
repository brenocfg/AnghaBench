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
typedef  size_t u8 ;
struct srpt_port {int /*<<< orphan*/  work; int /*<<< orphan*/  sm_lid; int /*<<< orphan*/  lid; } ;
struct srpt_device {TYPE_2__* device; struct srpt_port* port; } ;
struct ib_event_handler {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_num; } ;
struct ib_event {int event; TYPE_1__ element; TYPE_2__* device; } ;
struct TYPE_4__ {size_t phys_port_cnt; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  IB_EVENT_CLIENT_REREGISTER 134 
#define  IB_EVENT_GID_CHANGE 133 
#define  IB_EVENT_LID_CHANGE 132 
#define  IB_EVENT_PKEY_CHANGE 131 
#define  IB_EVENT_PORT_ACTIVE 130 
#define  IB_EVENT_PORT_ERR 129 
#define  IB_EVENT_SM_CHANGE 128 
 int /*<<< orphan*/  WARN (int,char*,int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct srpt_device* ib_get_client_data (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srpt_client ; 

__attribute__((used)) static void srpt_event_handler(struct ib_event_handler *handler,
			       struct ib_event *event)
{
	struct srpt_device *sdev;
	struct srpt_port *sport;
	u8 port_num;

	sdev = ib_get_client_data(event->device, &srpt_client);
	if (!sdev || sdev->device != event->device)
		return;

	pr_debug("ASYNC event= %d on device= %s\n", event->event,
		 dev_name(&sdev->device->dev));

	switch (event->event) {
	case IB_EVENT_PORT_ERR:
		port_num = event->element.port_num - 1;
		if (port_num < sdev->device->phys_port_cnt) {
			sport = &sdev->port[port_num];
			sport->lid = 0;
			sport->sm_lid = 0;
		} else {
			WARN(true, "event %d: port_num %d out of range 1..%d\n",
			     event->event, port_num + 1,
			     sdev->device->phys_port_cnt);
		}
		break;
	case IB_EVENT_PORT_ACTIVE:
	case IB_EVENT_LID_CHANGE:
	case IB_EVENT_PKEY_CHANGE:
	case IB_EVENT_SM_CHANGE:
	case IB_EVENT_CLIENT_REREGISTER:
	case IB_EVENT_GID_CHANGE:
		/* Refresh port data asynchronously. */
		port_num = event->element.port_num - 1;
		if (port_num < sdev->device->phys_port_cnt) {
			sport = &sdev->port[port_num];
			if (!sport->lid && !sport->sm_lid)
				schedule_work(&sport->work);
		} else {
			WARN(true, "event %d: port_num %d out of range 1..%d\n",
			     event->event, port_num + 1,
			     sdev->device->phys_port_cnt);
		}
		break;
	default:
		pr_err("received unrecognized IB event %d\n", event->event);
		break;
	}
}