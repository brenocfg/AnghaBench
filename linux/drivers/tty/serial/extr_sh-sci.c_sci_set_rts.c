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
typedef  int u16 ;
struct uart_port {scalar_t__ type; } ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ PORT_SCIFA ; 
 scalar_t__ PORT_SCIFB ; 
 int /*<<< orphan*/  SCPCR ; 
 int SCPCR_RTSC ; 
 int /*<<< orphan*/  SCPDR ; 
 int SCPDR_RTSD ; 
 int /*<<< orphan*/  SCSPTR ; 
 int SCSPTR_RTSDT ; 
 TYPE_1__* sci_getreg (struct uart_port*,int /*<<< orphan*/ ) ; 
 int serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sci_set_rts(struct uart_port *port, bool state)
{
	if (port->type == PORT_SCIFA || port->type == PORT_SCIFB) {
		u16 data = serial_port_in(port, SCPDR);

		/* Active low */
		if (state)
			data &= ~SCPDR_RTSD;
		else
			data |= SCPDR_RTSD;
		serial_port_out(port, SCPDR, data);

		/* RTS# is output */
		serial_port_out(port, SCPCR,
				serial_port_in(port, SCPCR) | SCPCR_RTSC);
	} else if (sci_getreg(port, SCSPTR)->size) {
		u16 ctrl = serial_port_in(port, SCSPTR);

		/* Active low */
		if (state)
			ctrl &= ~SCSPTR_RTSDT;
		else
			ctrl |= SCSPTR_RTSDT;
		serial_port_out(port, SCSPTR, ctrl);
	}
}