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
struct tty_struct {int index; struct sdio_uart_port* driver_data; } ;
struct tty_driver {int dummy; } ;
struct sdio_uart_port {int dummy; } ;

/* Variables and functions */
 struct sdio_uart_port* sdio_uart_port_get (int) ; 
 int /*<<< orphan*/  sdio_uart_port_put (struct sdio_uart_port*) ; 
 int tty_standard_install (struct tty_driver*,struct tty_struct*) ; 

__attribute__((used)) static int sdio_uart_install(struct tty_driver *driver, struct tty_struct *tty)
{
	int idx = tty->index;
	struct sdio_uart_port *port = sdio_uart_port_get(idx);
	int ret = tty_standard_install(driver, tty);

	if (ret == 0)
		/* This is the ref sdio_uart_port get provided */
		tty->driver_data = port;
	else
		sdio_uart_port_put(port);
	return ret;
}