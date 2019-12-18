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
 unsigned int UART_CTRL_TI ; 
 unsigned int UART_GET_CTRL (struct uart_port*) ; 
 int /*<<< orphan*/  UART_PUT_CTRL (struct uart_port*,unsigned int) ; 

__attribute__((used)) static void apbuart_stop_tx(struct uart_port *port)
{
	unsigned int cr;

	cr = UART_GET_CTRL(port);
	cr &= ~UART_CTRL_TI;
	UART_PUT_CTRL(port, cr);
}