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
struct earlycon_device {struct uart_port port; } ;
struct console {struct earlycon_device* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  serial_putc ; 
 int /*<<< orphan*/  uart_console_write (struct uart_port*,char const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void early_serial8250_write(struct console *console,
					const char *s, unsigned int count)
{
	struct earlycon_device *device = console->data;
	struct uart_port *port = &device->port;

	uart_console_write(port, s, count, serial_putc);
}