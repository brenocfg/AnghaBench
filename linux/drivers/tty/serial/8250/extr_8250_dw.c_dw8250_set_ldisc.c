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
struct uart_port {unsigned int (* serial_in ) (struct uart_port*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* serial_out ) (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ;} ;
struct uart_8250_port {int capabilities; } ;
struct ktermios {scalar_t__ c_line; } ;

/* Variables and functions */
 unsigned int DW_UART_MCR_SIRE ; 
 scalar_t__ N_IRDA ; 
 int UART_CAP_IRDA ; 
 int /*<<< orphan*/  UART_MCR ; 
 int /*<<< orphan*/  serial8250_do_set_ldisc (struct uart_port*,struct ktermios*) ; 
 unsigned int stub1 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static void dw8250_set_ldisc(struct uart_port *p, struct ktermios *termios)
{
	struct uart_8250_port *up = up_to_u8250p(p);
	unsigned int mcr = p->serial_in(p, UART_MCR);

	if (up->capabilities & UART_CAP_IRDA) {
		if (termios->c_line == N_IRDA)
			mcr |= DW_UART_MCR_SIRE;
		else
			mcr &= ~DW_UART_MCR_SIRE;

		p->serial_out(p, UART_MCR, mcr);
	}
	serial8250_do_set_ldisc(p, termios);
}