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
struct uart_port {int dummy; } ;
struct s3c24xx_uart_port {struct uart_port port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int S3C64XX_UINTM_RXD_MSK ; 
 unsigned int S3C64XX_UINTM_TXD_MSK ; 
 int /*<<< orphan*/  S3C64XX_UINTP ; 
 unsigned int rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c24xx_serial_rx_chars (int,void*) ; 
 int /*<<< orphan*/  s3c24xx_serial_tx_chars (int,void*) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static irqreturn_t s3c64xx_serial_handle_irq(int irq, void *id)
{
	struct s3c24xx_uart_port *ourport = id;
	struct uart_port *port = &ourport->port;
	unsigned int pend = rd_regl(port, S3C64XX_UINTP);
	irqreturn_t ret = IRQ_HANDLED;

	if (pend & S3C64XX_UINTM_RXD_MSK) {
		ret = s3c24xx_serial_rx_chars(irq, id);
		wr_regl(port, S3C64XX_UINTP, S3C64XX_UINTM_RXD_MSK);
	}
	if (pend & S3C64XX_UINTM_TXD_MSK) {
		ret = s3c24xx_serial_tx_chars(irq, id);
		wr_regl(port, S3C64XX_UINTP, S3C64XX_UINTM_TXD_MSK);
	}
	return ret;
}