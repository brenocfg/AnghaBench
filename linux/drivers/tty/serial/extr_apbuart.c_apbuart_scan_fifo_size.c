#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uart_port {int dummy; } ;

/* Variables and functions */
 int UART_CTRL_TE ; 
 int UART_GET_CTRL (struct uart_port*) ; 
 int UART_GET_STATUS (struct uart_port*) ; 
 int /*<<< orphan*/  UART_PUT_CHAR (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_PUT_CTRL (struct uart_port*,int) ; 
 int /*<<< orphan*/  UART_TX_READY (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int apbuart_scan_fifo_size(struct uart_port *port, int portnumber)
{
	int ctrl, loop = 0;
	int status;
	int fifosize;
	unsigned long flags;

	ctrl = UART_GET_CTRL(port);

	/*
	 * Enable the transceiver and wait for it to be ready to send data.
	 * Clear interrupts so that this process will not be externally
	 * interrupted in the middle (which can cause the transceiver to
	 * drain prematurely).
	 */

	local_irq_save(flags);

	UART_PUT_CTRL(port, ctrl | UART_CTRL_TE);

	while (!UART_TX_READY(UART_GET_STATUS(port)))
		loop++;

	/*
	 * Disable the transceiver so data isn't actually sent during the
	 * actual test.
	 */

	UART_PUT_CTRL(port, ctrl & ~(UART_CTRL_TE));

	fifosize = 1;
	UART_PUT_CHAR(port, 0);

	/*
	 * So long as transmitting a character increments the tranceivier FIFO
	 * length the FIFO must be at least that big. These bytes will
	 * automatically drain off of the FIFO.
	 */

	status = UART_GET_STATUS(port);
	while (((status >> 20) & 0x3F) == fifosize) {
		fifosize++;
		UART_PUT_CHAR(port, 0);
		status = UART_GET_STATUS(port);
	}

	fifosize--;

	UART_PUT_CTRL(port, ctrl);
	local_irq_restore(flags);

	if (fifosize == 0)
		fifosize = 1;

	return fifosize;
}