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
struct tegra_uart_port {int rts_active; } ;

/* Variables and functions */
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_LOOP ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  set_dtr (struct tegra_uart_port*,int) ; 
 int /*<<< orphan*/  set_loopbk (struct tegra_uart_port*,int) ; 
 int /*<<< orphan*/  set_rts (struct tegra_uart_port*,int) ; 
 struct tegra_uart_port* to_tegra_uport (struct uart_port*) ; 

__attribute__((used)) static void tegra_uart_set_mctrl(struct uart_port *u, unsigned int mctrl)
{
	struct tegra_uart_port *tup = to_tegra_uport(u);
	int enable;

	tup->rts_active = !!(mctrl & TIOCM_RTS);
	set_rts(tup, tup->rts_active);

	enable = !!(mctrl & TIOCM_DTR);
	set_dtr(tup, enable);

	enable = !!(mctrl & TIOCM_LOOP);
	set_loopbk(tup, enable);
}