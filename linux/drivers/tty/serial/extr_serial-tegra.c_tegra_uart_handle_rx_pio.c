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
struct tty_port {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx; } ;
struct TYPE_4__ {unsigned long ignore_status_mask; TYPE_1__ icount; } ;
struct tegra_uart_port {TYPE_2__ uport; } ;

/* Variables and functions */
 char TTY_NORMAL ; 
 int /*<<< orphan*/  UART_LSR ; 
 unsigned long UART_LSR_DR ; 
 int /*<<< orphan*/  UART_RX ; 
 char tegra_uart_decode_rx_error (struct tegra_uart_port*,unsigned long) ; 
 unsigned long tegra_uart_read (struct tegra_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,unsigned char,char) ; 
 int /*<<< orphan*/  uart_handle_sysrq_char (TYPE_2__*,unsigned char) ; 

__attribute__((used)) static void tegra_uart_handle_rx_pio(struct tegra_uart_port *tup,
		struct tty_port *tty)
{
	do {
		char flag = TTY_NORMAL;
		unsigned long lsr = 0;
		unsigned char ch;

		lsr = tegra_uart_read(tup, UART_LSR);
		if (!(lsr & UART_LSR_DR))
			break;

		flag = tegra_uart_decode_rx_error(tup, lsr);
		if (flag != TTY_NORMAL)
			continue;

		ch = (unsigned char) tegra_uart_read(tup, UART_RX);
		tup->uport.icount.rx++;

		if (!uart_handle_sysrq_char(&tup->uport, ch) && tty)
			tty_insert_flip_char(tty, ch, flag);

		if (tup->uport.ignore_status_mask & UART_LSR_DR)
			continue;
	} while (1);
}