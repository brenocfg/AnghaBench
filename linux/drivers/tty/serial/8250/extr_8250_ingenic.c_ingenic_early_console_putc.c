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
typedef  int uint8_t ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_LSR ; 
 int UART_LSR_TEMT ; 
 int /*<<< orphan*/  UART_TX ; 
 int early_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  early_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ingenic_early_console_putc(struct uart_port *port, int c)
{
	uint8_t lsr;

	do {
		lsr = early_in(port, UART_LSR);
	} while ((lsr & UART_LSR_TEMT) == 0);

	early_out(port, UART_TX, c);
}