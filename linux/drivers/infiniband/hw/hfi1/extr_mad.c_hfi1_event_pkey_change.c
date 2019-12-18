#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/  port_num; } ;
struct ib_event {TYPE_3__ element; int /*<<< orphan*/ * device; int /*<<< orphan*/  event; } ;
struct TYPE_4__ {int /*<<< orphan*/  ibdev; } ;
struct TYPE_5__ {TYPE_1__ rdi; } ;
struct hfi1_devdata {TYPE_2__ verbs_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_PKEY_CHANGE ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 

void hfi1_event_pkey_change(struct hfi1_devdata *dd, u8 port)
{
	struct ib_event event;

	event.event = IB_EVENT_PKEY_CHANGE;
	event.device = &dd->verbs_dev.rdi.ibdev;
	event.element.port_num = port;
	ib_dispatch_event(&event);
}