#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u8 ;
struct tegra_uart_port {unsigned long fcr_shadow; scalar_t__ rts_active; TYPE_1__* cdata; } ;
struct TYPE_2__ {scalar_t__ fifo_mode_enable_status; scalar_t__ allow_txfifo_reset_fifo_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_FCR ; 
 unsigned long UART_FCR_CLEAR_RCVR ; 
 unsigned long UART_FCR_CLEAR_XMIT ; 
 unsigned long UART_FCR_ENABLE_FIFO ; 
 int /*<<< orphan*/  UART_LSR ; 
 unsigned int UART_LSR_DR ; 
 unsigned int UART_LSR_TEMT ; 
 int /*<<< orphan*/  UART_SCR ; 
 int /*<<< orphan*/  set_rts (struct tegra_uart_port*,int) ; 
 unsigned int tegra_uart_read (struct tegra_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_uart_wait_cycle_time (struct tegra_uart_port*,int) ; 
 int /*<<< orphan*/  tegra_uart_wait_fifo_mode_enabled (struct tegra_uart_port*) ; 
 int /*<<< orphan*/  tegra_uart_write (struct tegra_uart_port*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tegra_uart_fifo_reset(struct tegra_uart_port *tup, u8 fcr_bits)
{
	unsigned long fcr = tup->fcr_shadow;
	unsigned int lsr, tmout = 10000;

	if (tup->rts_active)
		set_rts(tup, false);

	if (tup->cdata->allow_txfifo_reset_fifo_mode) {
		fcr |= fcr_bits & (UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
		tegra_uart_write(tup, fcr, UART_FCR);
	} else {
		fcr &= ~UART_FCR_ENABLE_FIFO;
		tegra_uart_write(tup, fcr, UART_FCR);
		udelay(60);
		fcr |= fcr_bits & (UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
		tegra_uart_write(tup, fcr, UART_FCR);
		fcr |= UART_FCR_ENABLE_FIFO;
		tegra_uart_write(tup, fcr, UART_FCR);
		if (tup->cdata->fifo_mode_enable_status)
			tegra_uart_wait_fifo_mode_enabled(tup);
	}

	/* Dummy read to ensure the write is posted */
	tegra_uart_read(tup, UART_SCR);

	/*
	 * For all tegra devices (up to t210), there is a hardware issue that
	 * requires software to wait for 32 UART clock periods for the flush
	 * to propagate, otherwise data could be lost.
	 */
	tegra_uart_wait_cycle_time(tup, 32);

	do {
		lsr = tegra_uart_read(tup, UART_LSR);
		if ((lsr | UART_LSR_TEMT) && !(lsr & UART_LSR_DR))
			break;
		udelay(1);
	} while (--tmout);

	if (tup->rts_active)
		set_rts(tup, true);
}