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
struct ib_event_handler {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  port_num; } ;
struct ib_event {TYPE_2__ element; TYPE_1__* device; int /*<<< orphan*/  event; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_event_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iser_event_handler(struct ib_event_handler *handler,
				struct ib_event *event)
{
	iser_err("async event %s (%d) on device %s port %d\n",
		 ib_event_msg(event->event), event->event,
		dev_name(&event->device->dev), event->element.port_num);
}