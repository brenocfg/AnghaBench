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
struct tegra_uart_port {unsigned long mcr_shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_MCR ; 
 unsigned long UART_MCR_DTR ; 
 int /*<<< orphan*/  tegra_uart_write (struct tegra_uart_port*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_dtr(struct tegra_uart_port *tup, bool active)
{
	unsigned long mcr;

	mcr = tup->mcr_shadow;
	if (active)
		mcr |= UART_MCR_DTR;
	else
		mcr &= ~UART_MCR_DTR;
	if (mcr != tup->mcr_shadow) {
		tegra_uart_write(tup, mcr, UART_MCR);
		tup->mcr_shadow = mcr;
	}
}