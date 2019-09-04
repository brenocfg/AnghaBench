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
struct mthca_dev {int /*<<< orphan*/  ib_dev; } ;
struct TYPE_2__ {int port_num; } ;
struct ib_event {TYPE_1__ element; int /*<<< orphan*/  event; int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ERR ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*,char*,int) ; 

__attribute__((used)) static void port_change(struct mthca_dev *dev, int port, int active)
{
	struct ib_event record;

	mthca_dbg(dev, "Port change to %s for port %d\n",
		  active ? "active" : "down", port);

	record.device = &dev->ib_dev;
	record.event  = active ? IB_EVENT_PORT_ACTIVE : IB_EVENT_PORT_ERR;
	record.element.port_num = port;

	ib_dispatch_event(&record);
}