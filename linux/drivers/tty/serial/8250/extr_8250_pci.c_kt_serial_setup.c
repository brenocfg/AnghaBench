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
struct TYPE_2__ {int /*<<< orphan*/  handle_break; int /*<<< orphan*/  serial_in; int /*<<< orphan*/  flags; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct serial_private {int dummy; } ;
struct pciserial_board {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPF_BUG_THRE ; 
 int /*<<< orphan*/  kt_handle_break ; 
 int /*<<< orphan*/  kt_serial_in ; 
 int skip_tx_en_setup (struct serial_private*,struct pciserial_board const*,struct uart_8250_port*,int) ; 

__attribute__((used)) static int kt_serial_setup(struct serial_private *priv,
			   const struct pciserial_board *board,
			   struct uart_8250_port *port, int idx)
{
	port->port.flags |= UPF_BUG_THRE;
	port->port.serial_in = kt_serial_in;
	port->port.handle_break = kt_handle_break;
	return skip_tx_en_setup(priv, board, port, idx);
}