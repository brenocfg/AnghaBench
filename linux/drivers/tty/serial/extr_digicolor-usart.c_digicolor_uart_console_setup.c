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
struct console {size_t index; } ;

/* Variables and functions */
 size_t DIGICOLOR_USART_NR ; 
 int EINVAL ; 
 int ENODEV ; 
 struct uart_port** digicolor_ports ; 
 int /*<<< orphan*/  uart_parse_options (char*,int*,int*,int*,int*) ; 
 int uart_set_options (struct uart_port*,struct console*,int,int,int,int) ; 

__attribute__((used)) static int digicolor_uart_console_setup(struct console *co, char *options)
{
	int baud = 115200, bits = 8, parity = 'n', flow = 'n';
	struct uart_port *port;

	if (co->index < 0 || co->index >= DIGICOLOR_USART_NR)
		return -EINVAL;

	port = digicolor_ports[co->index];
	if (!port)
		return -ENODEV;

	if (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	return uart_set_options(port, co, baud, parity, bits, flow);
}