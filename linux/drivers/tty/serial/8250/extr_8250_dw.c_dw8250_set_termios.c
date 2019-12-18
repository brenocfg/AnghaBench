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
struct uart_port {long uartclk; int /*<<< orphan*/  status; int /*<<< orphan*/  private_data; } ;
struct ktermios {int c_cflag; } ;
struct dw8250_data {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int CRTSCTS ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPSTAT_AUTOCTS ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 long clk_round_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int clk_set_rate (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  serial8250_do_set_termios (struct uart_port*,struct ktermios*,struct ktermios*) ; 
 struct dw8250_data* to_dw8250_data (int /*<<< orphan*/ ) ; 
 unsigned int tty_termios_baud_rate (struct ktermios*) ; 

__attribute__((used)) static void dw8250_set_termios(struct uart_port *p, struct ktermios *termios,
			       struct ktermios *old)
{
	unsigned int baud = tty_termios_baud_rate(termios);
	struct dw8250_data *d = to_dw8250_data(p->private_data);
	long rate;
	int ret;

	if (IS_ERR(d->clk))
		goto out;

	clk_disable_unprepare(d->clk);
	rate = clk_round_rate(d->clk, baud * 16);
	if (rate < 0)
		ret = rate;
	else if (rate == 0)
		ret = -ENOENT;
	else
		ret = clk_set_rate(d->clk, rate);
	clk_prepare_enable(d->clk);

	if (!ret)
		p->uartclk = rate;

out:
	p->status &= ~UPSTAT_AUTOCTS;
	if (termios->c_cflag & CRTSCTS)
		p->status |= UPSTAT_AUTOCTS;

	serial8250_do_set_termios(p, termios, old);
}