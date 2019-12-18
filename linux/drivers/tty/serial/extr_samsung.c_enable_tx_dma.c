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
struct s3c24xx_uart_port {int /*<<< orphan*/  tx_mode; int /*<<< orphan*/  tx_irq; struct uart_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_UCON ; 
 int /*<<< orphan*/  S3C24XX_TX_DMA ; 
 int S3C64XX_UCON_TXBURST_1 ; 
 int S3C64XX_UCON_TXBURST_16 ; 
 int S3C64XX_UCON_TXBURST_MASK ; 
 int S3C64XX_UCON_TXMODE_DMA ; 
 int S3C64XX_UCON_TXMODE_MASK ; 
 int /*<<< orphan*/  S3C64XX_UINTM ; 
 int /*<<< orphan*/  S3C64XX_UINTM_TXD ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int dma_get_cache_alignment () ; 
 int rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ s3c24xx_serial_has_interrupt_mask (struct uart_port*) ; 
 int /*<<< orphan*/  s3c24xx_set_bit (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enable_tx_dma(struct s3c24xx_uart_port *ourport)
{
	struct uart_port *port = &ourport->port;
	u32 ucon;

	/* Mask Tx interrupt */
	if (s3c24xx_serial_has_interrupt_mask(port))
		s3c24xx_set_bit(port, S3C64XX_UINTM_TXD, S3C64XX_UINTM);
	else
		disable_irq_nosync(ourport->tx_irq);

	/* Enable tx dma mode */
	ucon = rd_regl(port, S3C2410_UCON);
	ucon &= ~(S3C64XX_UCON_TXBURST_MASK | S3C64XX_UCON_TXMODE_MASK);
	ucon |= (dma_get_cache_alignment() >= 16) ?
		S3C64XX_UCON_TXBURST_16 : S3C64XX_UCON_TXBURST_1;
	ucon |= S3C64XX_UCON_TXMODE_DMA;
	wr_regl(port,  S3C2410_UCON, ucon);

	ourport->tx_mode = S3C24XX_TX_DMA;
}