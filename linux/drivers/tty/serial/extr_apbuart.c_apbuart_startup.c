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
struct uart_port {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 unsigned int UART_CTRL_RE ; 
 unsigned int UART_CTRL_RI ; 
 unsigned int UART_CTRL_TE ; 
 unsigned int UART_CTRL_TI ; 
 unsigned int UART_GET_CTRL (struct uart_port*) ; 
 int /*<<< orphan*/  UART_PUT_CTRL (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  apbuart_int ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uart_port*) ; 

__attribute__((used)) static int apbuart_startup(struct uart_port *port)
{
	int retval;
	unsigned int cr;

	/* Allocate the IRQ */
	retval = request_irq(port->irq, apbuart_int, 0, "apbuart", port);
	if (retval)
		return retval;

	/* Finally, enable interrupts */
	cr = UART_GET_CTRL(port);
	UART_PUT_CTRL(port,
		      cr | UART_CTRL_RE | UART_CTRL_TE |
		      UART_CTRL_RI | UART_CTRL_TI);

	return 0;
}