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
struct altera_tse_private {int /*<<< orphan*/  tx_dma_csr; int /*<<< orphan*/  dev; int /*<<< orphan*/  rx_dma_csr; } ;

/* Variables and functions */
 int ALTERA_TSE_SW_RESET_WATCHDOG_CNTR ; 
 int /*<<< orphan*/  MSGDMA_CSR_CTL_RESET ; 
 int /*<<< orphan*/  MSGDMA_CSR_STAT_MASK ; 
 int /*<<< orphan*/  MSGDMA_CSR_STAT_RESETTING ; 
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  csrwr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  msgdma_csroffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_warn (struct altera_tse_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  status ; 
 scalar_t__ tse_bit_is_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void msgdma_reset(struct altera_tse_private *priv)
{
	int counter;

	/* Reset Rx mSGDMA */
	csrwr32(MSGDMA_CSR_STAT_MASK, priv->rx_dma_csr,
		msgdma_csroffs(status));
	csrwr32(MSGDMA_CSR_CTL_RESET, priv->rx_dma_csr,
		msgdma_csroffs(control));

	counter = 0;
	while (counter++ < ALTERA_TSE_SW_RESET_WATCHDOG_CNTR) {
		if (tse_bit_is_clear(priv->rx_dma_csr, msgdma_csroffs(status),
				     MSGDMA_CSR_STAT_RESETTING))
			break;
		udelay(1);
	}

	if (counter >= ALTERA_TSE_SW_RESET_WATCHDOG_CNTR)
		netif_warn(priv, drv, priv->dev,
			   "TSE Rx mSGDMA resetting bit never cleared!\n");

	/* clear all status bits */
	csrwr32(MSGDMA_CSR_STAT_MASK, priv->rx_dma_csr, msgdma_csroffs(status));

	/* Reset Tx mSGDMA */
	csrwr32(MSGDMA_CSR_STAT_MASK, priv->tx_dma_csr,
		msgdma_csroffs(status));

	csrwr32(MSGDMA_CSR_CTL_RESET, priv->tx_dma_csr,
		msgdma_csroffs(control));

	counter = 0;
	while (counter++ < ALTERA_TSE_SW_RESET_WATCHDOG_CNTR) {
		if (tse_bit_is_clear(priv->tx_dma_csr, msgdma_csroffs(status),
				     MSGDMA_CSR_STAT_RESETTING))
			break;
		udelay(1);
	}

	if (counter >= ALTERA_TSE_SW_RESET_WATCHDOG_CNTR)
		netif_warn(priv, drv, priv->dev,
			   "TSE Tx mSGDMA resetting bit never cleared!\n");

	/* clear all status bits */
	csrwr32(MSGDMA_CSR_STAT_MASK, priv->tx_dma_csr, msgdma_csroffs(status));
}