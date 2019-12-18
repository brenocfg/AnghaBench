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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; int /*<<< orphan*/  irq; } ;
struct uart_txx9_port {TYPE_1__ port; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  TXX9_SIDICR ; 
 int TXX9_SIDICR_RIE ; 
 int /*<<< orphan*/  TXX9_SIDISR ; 
 int /*<<< orphan*/  TXX9_SIFCR ; 
 int TXX9_SIFCR_FRSTE ; 
 int TXX9_SIFCR_RFRST ; 
 int TXX9_SIFCR_TFRST ; 
 int /*<<< orphan*/  TXX9_SIFLCR ; 
 int TXX9_SIFLCR_RSDE ; 
 int TXX9_SIFLCR_TSDE ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uart_txx9_port*) ; 
 int /*<<< orphan*/  serial_txx9_interrupt ; 
 int /*<<< orphan*/  serial_txx9_set_mctrl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_mask (struct uart_txx9_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sio_out (struct uart_txx9_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_set (struct uart_txx9_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_txx9_port* to_uart_txx9_port (struct uart_port*) ; 

__attribute__((used)) static int serial_txx9_startup(struct uart_port *port)
{
	struct uart_txx9_port *up = to_uart_txx9_port(port);
	unsigned long flags;
	int retval;

	/*
	 * Clear the FIFO buffers and disable them.
	 * (they will be reenabled in set_termios())
	 */
	sio_set(up, TXX9_SIFCR,
		TXX9_SIFCR_TFRST | TXX9_SIFCR_RFRST | TXX9_SIFCR_FRSTE);
	/* clear reset */
	sio_mask(up, TXX9_SIFCR,
		 TXX9_SIFCR_TFRST | TXX9_SIFCR_RFRST | TXX9_SIFCR_FRSTE);
	sio_out(up, TXX9_SIDICR, 0);

	/*
	 * Clear the interrupt registers.
	 */
	sio_out(up, TXX9_SIDISR, 0);

	retval = request_irq(up->port.irq, serial_txx9_interrupt,
			     IRQF_SHARED, "serial_txx9", up);
	if (retval)
		return retval;

	/*
	 * Now, initialize the UART
	 */
	spin_lock_irqsave(&up->port.lock, flags);
	serial_txx9_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);

	/* Enable RX/TX */
	sio_mask(up, TXX9_SIFLCR, TXX9_SIFLCR_RSDE | TXX9_SIFLCR_TSDE);

	/*
	 * Finally, enable interrupts.
	 */
	sio_set(up, TXX9_SIDICR, TXX9_SIDICR_RIE);

	return 0;
}