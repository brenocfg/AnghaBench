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
struct tegra_uart_port {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned long TEGRA_UART_FCR_IIR_FIFO_EN ; 
 int /*<<< orphan*/  UART_IIR ; 
 unsigned long tegra_uart_read (struct tegra_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tegra_uart_wait_fifo_mode_enabled(struct tegra_uart_port *tup)
{
	unsigned long iir;
	unsigned int tmout = 100;

	do {
		iir = tegra_uart_read(tup, UART_IIR);
		if (iir & TEGRA_UART_FCR_IIR_FIFO_EN)
			return 0;
		udelay(1);
	} while (--tmout);

	return -ETIMEDOUT;
}