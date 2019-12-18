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
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  flags; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct serial_private {int dummy; } ;
struct pciserial_board {int uart_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_SUNIX ; 
 int /*<<< orphan*/  UPF_FIXED_TYPE ; 
 int div_s64_rem (int,int,int*) ; 
 int setup_port (struct serial_private*,struct uart_8250_port*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_sunix_setup(struct serial_private *priv,
		const struct pciserial_board *board,
		struct uart_8250_port *port, int idx)
{
	int bar;
	int offset;

	port->port.flags |= UPF_FIXED_TYPE;
	port->port.type = PORT_SUNIX;

	if (idx < 4) {
		bar = 0;
		offset = idx * board->uart_offset;
	} else {
		bar = 1;
		idx -= 4;
		idx = div_s64_rem(idx, 4, &offset);
		offset = idx * 64 + offset * board->uart_offset;
	}

	return setup_port(priv, port, bar, offset, 0);
}