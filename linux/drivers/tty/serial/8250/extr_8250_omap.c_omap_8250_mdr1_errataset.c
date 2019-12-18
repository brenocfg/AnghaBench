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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct uart_8250_port {int fcr; TYPE_1__ port; } ;
struct omap8250_priv {scalar_t__ mdr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_FCR ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 int /*<<< orphan*/  UART_LSR ; 
 scalar_t__ UART_LSR_DR ; 
 scalar_t__ UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_OMAP_MDR1 ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ serial_in (struct uart_8250_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void omap_8250_mdr1_errataset(struct uart_8250_port *up,
				     struct omap8250_priv *priv)
{
	u8 timeout = 255;
	u8 old_mdr1;

	old_mdr1 = serial_in(up, UART_OMAP_MDR1);
	if (old_mdr1 == priv->mdr1)
		return;

	serial_out(up, UART_OMAP_MDR1, priv->mdr1);
	udelay(2);
	serial_out(up, UART_FCR, up->fcr | UART_FCR_CLEAR_XMIT |
			UART_FCR_CLEAR_RCVR);
	/*
	 * Wait for FIFO to empty: when empty, RX_FIFO_E bit is 0 and
	 * TX_FIFO_E bit is 1.
	 */
	while (UART_LSR_THRE != (serial_in(up, UART_LSR) &
				(UART_LSR_THRE | UART_LSR_DR))) {
		timeout--;
		if (!timeout) {
			/* Should *never* happen. we warn and carry on */
			dev_crit(up->port.dev, "Errata i202: timedout %x\n",
				 serial_in(up, UART_LSR));
			break;
		}
		udelay(1);
	}
}