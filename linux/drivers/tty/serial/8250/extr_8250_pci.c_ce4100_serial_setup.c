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
struct TYPE_2__ {int flags; int regshift; int /*<<< orphan*/  type; int /*<<< orphan*/  iotype; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct serial_private {int dummy; } ;
struct pciserial_board {int /*<<< orphan*/  reg_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_XSCALE ; 
 int UPF_FIXED_PORT ; 
 int UPF_FIXED_TYPE ; 
 int /*<<< orphan*/  UPIO_MEM32 ; 
 int setup_port (struct serial_private*,struct uart_8250_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ce4100_serial_setup(struct serial_private *priv,
		  const struct pciserial_board *board,
		  struct uart_8250_port *port, int idx)
{
	int ret;

	ret = setup_port(priv, port, idx, 0, board->reg_shift);
	port->port.iotype = UPIO_MEM32;
	port->port.type = PORT_XSCALE;
	port->port.flags = (port->port.flags | UPF_FIXED_PORT | UPF_FIXED_TYPE);
	port->port.regshift = 2;

	return ret;
}