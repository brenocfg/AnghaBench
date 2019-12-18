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
struct uart_port {int /*<<< orphan*/  lock; } ;
struct tegra_uart_port {int /*<<< orphan*/  tx_in_progress; } ;

/* Variables and functions */
 unsigned int TIOCSER_TEMT ; 
 unsigned long TX_EMPTY_STATUS ; 
 int /*<<< orphan*/  UART_LSR ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long tegra_uart_read (struct tegra_uart_port*,int /*<<< orphan*/ ) ; 
 struct tegra_uart_port* to_tegra_uport (struct uart_port*) ; 

__attribute__((used)) static unsigned int tegra_uart_tx_empty(struct uart_port *u)
{
	struct tegra_uart_port *tup = to_tegra_uport(u);
	unsigned int ret = 0;
	unsigned long flags;

	spin_lock_irqsave(&u->lock, flags);
	if (!tup->tx_in_progress) {
		unsigned long lsr = tegra_uart_read(tup, UART_LSR);
		if ((lsr & TX_EMPTY_STATUS) == TX_EMPTY_STATUS)
			ret = TIOCSER_TEMT;
	}
	spin_unlock_irqrestore(&u->lock, flags);
	return ret;
}