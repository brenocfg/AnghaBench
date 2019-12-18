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
struct uart_8250_port {int ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_THRI ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool serial8250_clear_THRI(struct uart_8250_port *up)
{
	if (!(up->ier & UART_IER_THRI))
		return false;
	up->ier &= ~UART_IER_THRI;
	serial_out(up, UART_IER, up->ier);
	return true;
}