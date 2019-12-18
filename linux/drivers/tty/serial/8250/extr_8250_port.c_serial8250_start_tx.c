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
struct uart_8250_port {struct uart_8250_em485* em485; } ;
struct uart_8250_em485 {int /*<<< orphan*/  start_tx_timer; int /*<<< orphan*/ * active_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  __start_tx (struct uart_port*) ; 
 int /*<<< orphan*/  serial8250_rpm_get_tx (struct uart_8250_port*) ; 
 int /*<<< orphan*/  start_tx_rs485 (struct uart_port*) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static void serial8250_start_tx(struct uart_port *port)
{
	struct uart_8250_port *up = up_to_u8250p(port);
	struct uart_8250_em485 *em485 = up->em485;

	serial8250_rpm_get_tx(up);

	if (em485 &&
	    em485->active_timer == &em485->start_tx_timer)
		return;

	if (em485)
		start_tx_rs485(port);
	else
		__start_tx(port);
}