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
typedef  int u16 ;
struct TYPE_6__ {int /*<<< orphan*/  overrun; } ;
struct uart_port {int /*<<< orphan*/  dev; TYPE_3__ icount; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct sci_port {TYPE_2__* params; } ;
struct plat_sci_reg {int /*<<< orphan*/  size; } ;
struct TYPE_5__ {int overrun_mask; int /*<<< orphan*/  overrun_reg; } ;
struct TYPE_4__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_OVERRUN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct plat_sci_reg* sci_getreg (struct uart_port*,int /*<<< orphan*/ ) ; 
 int serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sci_handle_fifo_overrun(struct uart_port *port)
{
	struct tty_port *tport = &port->state->port;
	struct sci_port *s = to_sci_port(port);
	const struct plat_sci_reg *reg;
	int copied = 0;
	u16 status;

	reg = sci_getreg(port, s->params->overrun_reg);
	if (!reg->size)
		return 0;

	status = serial_port_in(port, s->params->overrun_reg);
	if (status & s->params->overrun_mask) {
		status &= ~s->params->overrun_mask;
		serial_port_out(port, s->params->overrun_reg, status);

		port->icount.overrun++;

		tty_insert_flip_char(tport, 0, TTY_OVERRUN);
		tty_flip_buffer_push(tport);

		dev_dbg(port->dev, "overrun error\n");
		copied++;
	}

	return copied;
}