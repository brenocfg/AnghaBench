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
struct uart_8250_port {int /*<<< orphan*/  fcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_FCR ; 
 int /*<<< orphan*/  serial8250_clear_fifos (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void serial8250_clear_and_reinit_fifos(struct uart_8250_port *p)
{
	serial8250_clear_fifos(p);
	serial_out(p, UART_FCR, p->fcr);
}