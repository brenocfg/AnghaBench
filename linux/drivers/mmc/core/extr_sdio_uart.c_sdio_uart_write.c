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
struct tty_struct {struct sdio_uart_port* driver_data; } ;
struct sdio_uart_port {int ier; int /*<<< orphan*/  func; int /*<<< orphan*/  write_lock; int /*<<< orphan*/  xmit_fifo; } ;

/* Variables and functions */
 int ENODEV ; 
 int UART_IER_THRI ; 
 int kfifo_in_locked (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ *) ; 
 int sdio_uart_claim_func (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_uart_release_func (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_start_tx (struct sdio_uart_port*) ; 

__attribute__((used)) static int sdio_uart_write(struct tty_struct *tty, const unsigned char *buf,
			   int count)
{
	struct sdio_uart_port *port = tty->driver_data;
	int ret;

	if (!port->func)
		return -ENODEV;

	ret = kfifo_in_locked(&port->xmit_fifo, buf, count, &port->write_lock);
	if (!(port->ier & UART_IER_THRI)) {
		int err = sdio_uart_claim_func(port);
		if (!err) {
			sdio_uart_start_tx(port);
			sdio_uart_irq(port->func);
			sdio_uart_release_func(port);
		} else
			ret = err;
	}

	return ret;
}