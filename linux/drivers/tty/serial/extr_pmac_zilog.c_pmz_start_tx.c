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
struct TYPE_4__ {int /*<<< orphan*/  tx; } ;
struct uart_port {TYPE_2__ icount; TYPE_1__* state; scalar_t__ x_char; } ;
struct uart_pmac_port {int /*<<< orphan*/  port; int /*<<< orphan*/  flags; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMACZILOG_FLAG_TX_ACTIVE ; 
 int /*<<< orphan*/  PMACZILOG_FLAG_TX_STOPPED ; 
 int /*<<< orphan*/  R0 ; 
 unsigned char Tx_BUF_EMP ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  pmz_debug (char*) ; 
 unsigned char read_zsreg (struct uart_pmac_port*,int /*<<< orphan*/ ) ; 
 struct uart_pmac_port* to_pmz (struct uart_port*) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_zsdata (struct uart_pmac_port*,scalar_t__) ; 
 int /*<<< orphan*/  zssync (struct uart_pmac_port*) ; 

__attribute__((used)) static void pmz_start_tx(struct uart_port *port)
{
	struct uart_pmac_port *uap = to_pmz(port);
	unsigned char status;

	pmz_debug("pmz: start_tx()\n");

	uap->flags |= PMACZILOG_FLAG_TX_ACTIVE;
	uap->flags &= ~PMACZILOG_FLAG_TX_STOPPED;

	status = read_zsreg(uap, R0);

	/* TX busy?  Just wait for the TX done interrupt.  */
	if (!(status & Tx_BUF_EMP))
		return;

	/* Send the first character to jump-start the TX done
	 * IRQ sending engine.
	 */
	if (port->x_char) {
		write_zsdata(uap, port->x_char);
		zssync(uap);
		port->icount.tx++;
		port->x_char = 0;
	} else {
		struct circ_buf *xmit = &port->state->xmit;

		if (uart_circ_empty(xmit))
			goto out;
		write_zsdata(uap, xmit->buf[xmit->tail]);
		zssync(uap);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;

		if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
			uart_write_wakeup(&uap->port);
	}
 out:
	pmz_debug("pmz: start_tx() done.\n");
}