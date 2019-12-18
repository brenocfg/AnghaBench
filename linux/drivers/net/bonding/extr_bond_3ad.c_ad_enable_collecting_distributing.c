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
struct port {TYPE_3__* aggregator; int /*<<< orphan*/  actor_port_number; TYPE_2__* slave; } ;
struct TYPE_6__ {int /*<<< orphan*/  aggregator_identifier; scalar_t__ is_active; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; TYPE_1__* bond; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __enable_port (struct port*) ; 
 int /*<<< orphan*/  slave_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad_enable_collecting_distributing(struct port *port,
					      bool *update_slave_arr)
{
	if (port->aggregator->is_active) {
		slave_dbg(port->slave->bond->dev, port->slave->dev,
			  "Enabling port %d (LAG %d)\n",
			  port->actor_port_number,
			  port->aggregator->aggregator_identifier);
		__enable_port(port);
		/* Slave array needs update */
		*update_slave_arr = true;
	}
}