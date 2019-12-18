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
typedef  int /*<<< orphan*/  u8 ;
struct siw_device {int /*<<< orphan*/  base_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_num; } ;
struct ib_event {int event; TYPE_1__ element; int /*<<< orphan*/ * device; } ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 
 int /*<<< orphan*/  siw_dbg (int /*<<< orphan*/ *,char*,int) ; 

void siw_port_event(struct siw_device *sdev, u8 port, enum ib_event_type etype)
{
	struct ib_event event;

	event.event = etype;
	event.device = &sdev->base_dev;
	event.element.port_num = port;

	siw_dbg(&sdev->base_dev, "reporting port event %d\n", etype);

	ib_dispatch_event(&event);
}