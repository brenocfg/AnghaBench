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
struct TYPE_2__ {int port_num; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_1__ element; int /*<<< orphan*/ * device; } ;
struct i40iw_ib_device {int /*<<< orphan*/  ibdev; } ;
struct i40iw_device {scalar_t__ iw_status; struct i40iw_ib_device* iwibdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ERR ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 

void i40iw_port_ibevent(struct i40iw_device *iwdev)
{
	struct i40iw_ib_device *iwibdev = iwdev->iwibdev;
	struct ib_event event;

	event.device = &iwibdev->ibdev;
	event.element.port_num = 1;
	event.event = iwdev->iw_status ? IB_EVENT_PORT_ACTIVE : IB_EVENT_PORT_ERR;
	ib_dispatch_event(&event);
}