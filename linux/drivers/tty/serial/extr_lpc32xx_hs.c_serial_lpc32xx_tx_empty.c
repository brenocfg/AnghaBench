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
struct uart_port {int /*<<< orphan*/  membase; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_HSUART_LEVEL (int /*<<< orphan*/ ) ; 
 scalar_t__ LPC32XX_HSU_TX_LEV (int /*<<< orphan*/ ) ; 
 unsigned int TIOCSER_TEMT ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int serial_lpc32xx_tx_empty(struct uart_port *port)
{
	unsigned int ret = 0;

	if (LPC32XX_HSU_TX_LEV(readl(LPC32XX_HSUART_LEVEL(port->membase))) == 0)
		ret = TIOCSER_TEMT;

	return ret;
}