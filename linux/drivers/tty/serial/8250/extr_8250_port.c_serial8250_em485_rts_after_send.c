#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ rs485; } ;
struct uart_8250_port {TYPE_2__ port; } ;

/* Variables and functions */
 int SER_RS485_RTS_AFTER_SEND ; 
 unsigned char UART_MCR_RTS ; 
 unsigned char serial8250_in_MCR (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_out_MCR (struct uart_8250_port*,unsigned char) ; 

__attribute__((used)) static inline void serial8250_em485_rts_after_send(struct uart_8250_port *p)
{
	unsigned char mcr = serial8250_in_MCR(p);

	if (p->port.rs485.flags & SER_RS485_RTS_AFTER_SEND)
		mcr |= UART_MCR_RTS;
	else
		mcr &= ~UART_MCR_RTS;
	serial8250_out_MCR(p, mcr);
}