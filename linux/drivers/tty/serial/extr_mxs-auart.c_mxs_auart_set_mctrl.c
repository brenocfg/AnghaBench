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
typedef  int u32 ;
struct uart_port {int dummy; } ;
struct mxs_auart_port {int /*<<< orphan*/  gpios; } ;

/* Variables and functions */
 int AUART_CTRL2_RTS ; 
 int AUART_CTRL2_RTSEN ; 
 int /*<<< orphan*/  REG_CTRL2 ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  mctrl_gpio_set (int /*<<< orphan*/ ,unsigned int) ; 
 int mxs_read (struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_write (int,struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 struct mxs_auart_port* to_auart_port (struct uart_port*) ; 
 scalar_t__ uart_cts_enabled (struct uart_port*) ; 

__attribute__((used)) static void mxs_auart_set_mctrl(struct uart_port *u, unsigned mctrl)
{
	struct mxs_auart_port *s = to_auart_port(u);

	u32 ctrl = mxs_read(s, REG_CTRL2);

	ctrl &= ~(AUART_CTRL2_RTSEN | AUART_CTRL2_RTS);
	if (mctrl & TIOCM_RTS) {
		if (uart_cts_enabled(u))
			ctrl |= AUART_CTRL2_RTSEN;
		else
			ctrl |= AUART_CTRL2_RTS;
	}

	mxs_write(ctrl, s, REG_CTRL2);

	mctrl_gpio_set(s->gpios, mctrl);
}