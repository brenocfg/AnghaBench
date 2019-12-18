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
typedef  int u32 ;
struct uart_port {unsigned long uartclk; int /*<<< orphan*/  status; scalar_t__ membase; int /*<<< orphan*/  private_data; } ;
struct lpss8250 {TYPE_1__* board; } ;
struct ktermios {int c_cflag; } ;
struct TYPE_2__ {unsigned long freq; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ BYT_PRV_CLK ; 
 int BYT_PRV_CLK_EN ; 
 unsigned long BYT_PRV_CLK_M_VAL_SHIFT ; 
 unsigned long BYT_PRV_CLK_N_VAL_SHIFT ; 
 int BYT_PRV_CLK_UPDATE ; 
 int CRTSCTS ; 
 int /*<<< orphan*/  UPSTAT_AUTOCTS ; 
 int /*<<< orphan*/  rational_best_approximation (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long*,unsigned long*) ; 
 unsigned long rounddown_pow_of_two (unsigned long) ; 
 int /*<<< orphan*/  serial8250_do_set_termios (struct uart_port*,struct ktermios*,struct ktermios*) ; 
 struct lpss8250* to_lpss8250 (int /*<<< orphan*/ ) ; 
 unsigned int tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void byt_set_termios(struct uart_port *p, struct ktermios *termios,
			    struct ktermios *old)
{
	unsigned int baud = tty_termios_baud_rate(termios);
	struct lpss8250 *lpss = to_lpss8250(p->private_data);
	unsigned long fref = lpss->board->freq, fuart = baud * 16;
	unsigned long w = BIT(15) - 1;
	unsigned long m, n;
	u32 reg;

	/* Gracefully handle the B0 case: fall back to B9600 */
	fuart = fuart ? fuart : 9600 * 16;

	/* Get Fuart closer to Fref */
	fuart *= rounddown_pow_of_two(fref / fuart);

	/*
	 * For baud rates 0.5M, 1M, 1.5M, 2M, 2.5M, 3M, 3.5M and 4M the
	 * dividers must be adjusted.
	 *
	 * uartclk = (m / n) * 100 MHz, where m <= n
	 */
	rational_best_approximation(fuart, fref, w, w, &m, &n);
	p->uartclk = fuart;

	/* Reset the clock */
	reg = (m << BYT_PRV_CLK_M_VAL_SHIFT) | (n << BYT_PRV_CLK_N_VAL_SHIFT);
	writel(reg, p->membase + BYT_PRV_CLK);
	reg |= BYT_PRV_CLK_EN | BYT_PRV_CLK_UPDATE;
	writel(reg, p->membase + BYT_PRV_CLK);

	p->status &= ~UPSTAT_AUTOCTS;
	if (termios->c_cflag & CRTSCTS)
		p->status |= UPSTAT_AUTOCTS;

	serial8250_do_set_termios(p, termios, old);
}