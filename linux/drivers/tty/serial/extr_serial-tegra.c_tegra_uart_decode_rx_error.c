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
struct TYPE_3__ {int /*<<< orphan*/  brk; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; } ;
struct TYPE_4__ {unsigned long ignore_status_mask; int /*<<< orphan*/  dev; TYPE_1__ icount; } ;
struct tegra_uart_port {TYPE_2__ uport; } ;

/* Variables and functions */
 unsigned long TEGRA_UART_LSR_ANY ; 
 char TTY_BREAK ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_OVERRUN ; 
 char TTY_PARITY ; 
 int /*<<< orphan*/  UART_FCR_CLEAR_RCVR ; 
 unsigned long UART_LSR_BI ; 
 unsigned long UART_LSR_DR ; 
 unsigned long UART_LSR_FE ; 
 unsigned long UART_LSR_FIFOE ; 
 unsigned long UART_LSR_OE ; 
 unsigned long UART_LSR_PE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tegra_uart_fifo_reset (struct tegra_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_insert_char (TYPE_2__*,unsigned long,unsigned long,int /*<<< orphan*/ ,char) ; 
 scalar_t__ unlikely (unsigned long) ; 

__attribute__((used)) static char tegra_uart_decode_rx_error(struct tegra_uart_port *tup,
			unsigned long lsr)
{
	char flag = TTY_NORMAL;

	if (unlikely(lsr & TEGRA_UART_LSR_ANY)) {
		if (lsr & UART_LSR_OE) {
			/* Overrrun error */
			flag = TTY_OVERRUN;
			tup->uport.icount.overrun++;
			dev_err(tup->uport.dev, "Got overrun errors\n");
		} else if (lsr & UART_LSR_PE) {
			/* Parity error */
			flag = TTY_PARITY;
			tup->uport.icount.parity++;
			dev_err(tup->uport.dev, "Got Parity errors\n");
		} else if (lsr & UART_LSR_FE) {
			flag = TTY_FRAME;
			tup->uport.icount.frame++;
			dev_err(tup->uport.dev, "Got frame errors\n");
		} else if (lsr & UART_LSR_BI) {
			/*
			 * Break error
			 * If FIFO read error without any data, reset Rx FIFO
			 */
			if (!(lsr & UART_LSR_DR) && (lsr & UART_LSR_FIFOE))
				tegra_uart_fifo_reset(tup, UART_FCR_CLEAR_RCVR);
			if (tup->uport.ignore_status_mask & UART_LSR_BI)
				return TTY_BREAK;
			flag = TTY_BREAK;
			tup->uport.icount.brk++;
			dev_dbg(tup->uport.dev, "Got Break\n");
		}
		uart_insert_char(&tup->uport, lsr, UART_LSR_OE, 0, flag);
	}

	return flag;
}