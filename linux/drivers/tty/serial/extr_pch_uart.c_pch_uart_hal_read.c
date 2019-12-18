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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  brk; } ;
struct uart_port {scalar_t__ sysrq; TYPE_1__ icount; } ;
struct eg20t_port {scalar_t__ membase; struct uart_port port; } ;

/* Variables and functions */
 scalar_t__ PCH_UART_RBR ; 
 scalar_t__ UART_LSR ; 
 int UART_LSR_BI ; 
 int UART_LSR_DR ; 
 int ioread8 (scalar_t__) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,int) ; 

__attribute__((used)) static int pch_uart_hal_read(struct eg20t_port *priv, unsigned char *buf,
			     int rx_size)
{
	int i;
	u8 rbr, lsr;
	struct uart_port *port = &priv->port;

	lsr = ioread8(priv->membase + UART_LSR);
	for (i = 0, lsr = ioread8(priv->membase + UART_LSR);
	     i < rx_size && lsr & (UART_LSR_DR | UART_LSR_BI);
	     lsr = ioread8(priv->membase + UART_LSR)) {
		rbr = ioread8(priv->membase + PCH_UART_RBR);

		if (lsr & UART_LSR_BI) {
			port->icount.brk++;
			if (uart_handle_break(port))
				continue;
		}
#ifdef SUPPORT_SYSRQ
		if (port->sysrq) {
			if (uart_handle_sysrq_char(port, rbr))
				continue;
		}
#endif

		buf[i++] = rbr;
	}
	return i;
}