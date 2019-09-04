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
struct qedr_dev {int /*<<< orphan*/  ibdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_num; } ;
struct ib_event {int event; TYPE_1__ element; int /*<<< orphan*/ * device; } ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 

__attribute__((used)) static void qedr_ib_dispatch_event(struct qedr_dev *dev, u8 port_num,
				   enum ib_event_type type)
{
	struct ib_event ibev;

	ibev.device = &dev->ibdev;
	ibev.element.port_num = port_num;
	ibev.event = type;

	ib_dispatch_event(&ibev);
}