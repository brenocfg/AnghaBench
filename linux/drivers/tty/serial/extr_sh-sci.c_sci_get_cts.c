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
struct uart_port {scalar_t__ type; } ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ PORT_SCIFA ; 
 scalar_t__ PORT_SCIFB ; 
 int /*<<< orphan*/  SCPDR ; 
 int SCPDR_CTSD ; 
 int /*<<< orphan*/  SCSPTR ; 
 int SCSPTR_CTSDT ; 
 TYPE_1__* sci_getreg (struct uart_port*,int /*<<< orphan*/ ) ; 
 int serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sci_get_cts(struct uart_port *port)
{
	if (port->type == PORT_SCIFA || port->type == PORT_SCIFB) {
		/* Active low */
		return !(serial_port_in(port, SCPDR) & SCPDR_CTSD);
	} else if (sci_getreg(port, SCSPTR)->size) {
		/* Active low */
		return !(serial_port_in(port, SCSPTR) & SCSPTR_CTSDT);
	}

	return true;
}