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
struct uart_port {unsigned long uartclk; scalar_t__ membase; struct mid8250* private_data; } ;
struct mid8250 {TYPE_1__* board; } ;
struct ktermios {int dummy; } ;
struct TYPE_2__ {unsigned long freq; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ INTEL_MID_UART_DIV ; 
 scalar_t__ INTEL_MID_UART_MUL ; 
 scalar_t__ INTEL_MID_UART_PS ; 
 int /*<<< orphan*/  rational_best_approximation (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long*,unsigned long*) ; 
 unsigned long rounddown_pow_of_two (unsigned long) ; 
 int /*<<< orphan*/  serial8250_do_set_termios (struct uart_port*,struct ktermios*,struct ktermios*) ; 
 unsigned int tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void mid8250_set_termios(struct uart_port *p,
				struct ktermios *termios,
				struct ktermios *old)
{
	unsigned int baud = tty_termios_baud_rate(termios);
	struct mid8250 *mid = p->private_data;
	unsigned short ps = 16;
	unsigned long fuart = baud * ps;
	unsigned long w = BIT(24) - 1;
	unsigned long mul, div;

	/* Gracefully handle the B0 case: fall back to B9600 */
	fuart = fuart ? fuart : 9600 * 16;

	if (mid->board->freq < fuart) {
		/* Find prescaler value that satisfies Fuart < Fref */
		if (mid->board->freq > baud)
			ps = mid->board->freq / baud;	/* baud rate too high */
		else
			ps = 1;				/* PLL case */
		fuart = baud * ps;
	} else {
		/* Get Fuart closer to Fref */
		fuart *= rounddown_pow_of_two(mid->board->freq / fuart);
	}

	rational_best_approximation(fuart, mid->board->freq, w, w, &mul, &div);
	p->uartclk = fuart * 16 / ps;		/* core uses ps = 16 always */

	writel(ps, p->membase + INTEL_MID_UART_PS);		/* set PS */
	writel(mul, p->membase + INTEL_MID_UART_MUL);		/* set MUL */
	writel(div, p->membase + INTEL_MID_UART_DIV);

	serial8250_do_set_termios(p, termios, old);
}