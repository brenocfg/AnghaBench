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
struct pvrdma_dev {int /*<<< orphan*/  ib_dev; } ;
struct TYPE_2__ {int port_num; } ;
struct ib_event {int event; TYPE_1__ element; int /*<<< orphan*/ * device; } ;
typedef  int /*<<< orphan*/  ib_event ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 
 int /*<<< orphan*/  memset (struct ib_event*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pvrdma_dispatch_event(struct pvrdma_dev *dev, int port,
				  enum ib_event_type event)
{
	struct ib_event ib_event;

	memset(&ib_event, 0, sizeof(ib_event));
	ib_event.device = &dev->ib_dev;
	ib_event.element.port_num = port;
	ib_event.event = event;
	ib_dispatch_event(&ib_event);
}