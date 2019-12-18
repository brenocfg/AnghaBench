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
 int /*<<< orphan*/  SC16IS7XX_LCR_REG ; 
 int /*<<< orphan*/  SC16IS7XX_LCR_TXBREAK_BIT ; 
 int /*<<< orphan*/  sc16is7xx_port_update (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sc16is7xx_break_ctl(struct uart_port *port, int break_state)
{
	sc16is7xx_port_update(port, SC16IS7XX_LCR_REG,
			      SC16IS7XX_LCR_TXBREAK_BIT,
			      break_state ? SC16IS7XX_LCR_TXBREAK_BIT : 0);
}