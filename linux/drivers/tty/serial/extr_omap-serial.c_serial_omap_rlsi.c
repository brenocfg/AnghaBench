#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; } ;
struct TYPE_7__ {scalar_t__ line; TYPE_2__* cons; TYPE_1__ icount; } ;
struct uart_omap_port {unsigned int lsr_break_flag; TYPE_3__ port; } ;
struct TYPE_6__ {scalar_t__ index; } ;

/* Variables and functions */
 unsigned int TTY_BREAK ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_PARITY ; 
 unsigned int UART_LSR_BI ; 
 unsigned int UART_LSR_DR ; 
 unsigned int UART_LSR_FE ; 
 unsigned int UART_LSR_OE ; 
 unsigned int UART_LSR_PE ; 
 int /*<<< orphan*/  UART_RX ; 
 scalar_t__ likely (unsigned int) ; 
 unsigned char serial_in (struct uart_omap_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_handle_break (TYPE_3__*) ; 
 int /*<<< orphan*/  uart_insert_char (TYPE_3__*,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void serial_omap_rlsi(struct uart_omap_port *up, unsigned int lsr)
{
	unsigned int flag;
	unsigned char ch = 0;

	if (likely(lsr & UART_LSR_DR))
		ch = serial_in(up, UART_RX);

	up->port.icount.rx++;
	flag = TTY_NORMAL;

	if (lsr & UART_LSR_BI) {
		flag = TTY_BREAK;
		lsr &= ~(UART_LSR_FE | UART_LSR_PE);
		up->port.icount.brk++;
		/*
		 * We do the SysRQ and SAK checking
		 * here because otherwise the break
		 * may get masked by ignore_status_mask
		 * or read_status_mask.
		 */
		if (uart_handle_break(&up->port))
			return;

	}

	if (lsr & UART_LSR_PE) {
		flag = TTY_PARITY;
		up->port.icount.parity++;
	}

	if (lsr & UART_LSR_FE) {
		flag = TTY_FRAME;
		up->port.icount.frame++;
	}

	if (lsr & UART_LSR_OE)
		up->port.icount.overrun++;

#ifdef CONFIG_SERIAL_OMAP_CONSOLE
	if (up->port.line == up->port.cons->index) {
		/* Recover the break flag from console xmit */
		lsr |= up->lsr_break_flag;
	}
#endif
	uart_insert_char(&up->port, lsr, UART_LSR_OE, 0, flag);
}