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
struct sdio_uart_port {int /*<<< orphan*/  xmit_fifo; } ;

/* Variables and functions */
 int FIFO_SIZE ; 
 int kfifo_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sdio_uart_write_room(struct tty_struct *tty)
{
	struct sdio_uart_port *port = tty->driver_data;
	return FIFO_SIZE - kfifo_len(&port->xmit_fifo);
}