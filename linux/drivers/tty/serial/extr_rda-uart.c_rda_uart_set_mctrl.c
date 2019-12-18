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

/* Variables and functions */
 int /*<<< orphan*/  RDA_UART_CMD_CLR ; 
 int /*<<< orphan*/  RDA_UART_CMD_SET ; 
 int /*<<< orphan*/  RDA_UART_CTRL ; 
 int RDA_UART_LOOP_BACK_EN ; 
 int RDA_UART_RTS ; 
 unsigned int TIOCM_LOOP ; 
 unsigned int TIOCM_RTS ; 
 int rda_uart_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rda_uart_write (struct uart_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rda_uart_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	u32 val;

	if (mctrl & TIOCM_RTS) {
		val = rda_uart_read(port, RDA_UART_CMD_SET);
		rda_uart_write(port, (val | RDA_UART_RTS), RDA_UART_CMD_SET);
	} else {
		/* Clear RTS to stop to receive. */
		val = rda_uart_read(port, RDA_UART_CMD_CLR);
		rda_uart_write(port, (val | RDA_UART_RTS), RDA_UART_CMD_CLR);
	}

	val = rda_uart_read(port, RDA_UART_CTRL);

	if (mctrl & TIOCM_LOOP)
		val |= RDA_UART_LOOP_BACK_EN;
	else
		val &= ~RDA_UART_LOOP_BACK_EN;

	rda_uart_write(port, val, RDA_UART_CTRL);
}