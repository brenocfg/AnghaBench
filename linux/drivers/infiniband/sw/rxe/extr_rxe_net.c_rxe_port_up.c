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
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct rxe_port {TYPE_1__ attr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct rxe_dev {TYPE_2__ ib_dev; struct rxe_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_PORT_ACTIVE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rxe_port_event (struct rxe_dev*,int /*<<< orphan*/ ) ; 

void rxe_port_up(struct rxe_dev *rxe)
{
	struct rxe_port *port;

	port = &rxe->port;
	port->attr.state = IB_PORT_ACTIVE;

	rxe_port_event(rxe, IB_EVENT_PORT_ACTIVE);
	dev_info(&rxe->ib_dev.dev, "set active\n");
}