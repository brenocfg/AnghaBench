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
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  parity; int /*<<< orphan*/  rx; } ;
struct uart_port {int read_status_mask; scalar_t__ membase; TYPE_2__ icount; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 int MLB_USIO_FCR_FE2 ; 
 int MLB_USIO_FCR_FRIIE ; 
 scalar_t__ MLB_USIO_REG_DR ; 
 scalar_t__ MLB_USIO_REG_FBYTE ; 
 scalar_t__ MLB_USIO_REG_FCR ; 
 scalar_t__ MLB_USIO_REG_SSR ; 
 int MLB_USIO_SSR_BRK ; 
 int MLB_USIO_SSR_FRE ; 
 int MLB_USIO_SSR_ORE ; 
 int MLB_USIO_SSR_PE ; 
 int MLB_USIO_SSR_RDRF ; 
 int MLB_USIO_SSR_REC ; 
 unsigned long TTY_BREAK ; 
 unsigned long TTY_FRAME ; 
 unsigned long TTY_NORMAL ; 
 unsigned long TTY_PARITY ; 
 int readb (scalar_t__) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,char) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,int,int,char,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void mlb_usio_rx_chars(struct uart_port *port)
{
	struct tty_port *ttyport = &port->state->port;
	unsigned long flag = 0;
	char ch = 0;
	u8 status;
	int max_count = 2;

	while (max_count--) {
		status = readb(port->membase + MLB_USIO_REG_SSR);

		if (!(status & MLB_USIO_SSR_RDRF))
			break;

		if (!(status & (MLB_USIO_SSR_ORE | MLB_USIO_SSR_FRE |
				MLB_USIO_SSR_PE))) {
			ch = readw(port->membase + MLB_USIO_REG_DR);
			flag = TTY_NORMAL;
			port->icount.rx++;
			if (uart_handle_sysrq_char(port, ch))
				continue;
			uart_insert_char(port, status, MLB_USIO_SSR_ORE,
					 ch, flag);
			continue;
		}
		if (status & MLB_USIO_SSR_PE)
			port->icount.parity++;
		if (status & MLB_USIO_SSR_ORE)
			port->icount.overrun++;
		status &= port->read_status_mask;
		if (status & MLB_USIO_SSR_BRK) {
			flag = TTY_BREAK;
			ch = 0;
		} else
			if (status & MLB_USIO_SSR_PE) {
				flag = TTY_PARITY;
				ch = 0;
			} else
				if (status & MLB_USIO_SSR_FRE) {
					flag = TTY_FRAME;
					ch = 0;
				}
		if (flag)
			uart_insert_char(port, status, MLB_USIO_SSR_ORE,
					 ch, flag);

		writeb(readb(port->membase + MLB_USIO_REG_SSR) |
				MLB_USIO_SSR_REC,
				port->membase + MLB_USIO_REG_SSR);

		max_count = readw(port->membase + MLB_USIO_REG_FBYTE) >> 8;
		writew(readw(port->membase + MLB_USIO_REG_FCR) |
		       MLB_USIO_FCR_FE2 | MLB_USIO_FCR_FRIIE,
		port->membase + MLB_USIO_REG_FCR);
	}

	tty_flip_buffer_push(ttyport);
}