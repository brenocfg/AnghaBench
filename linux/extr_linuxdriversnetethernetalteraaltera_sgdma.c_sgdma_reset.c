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
struct altera_tse_private {int /*<<< orphan*/  rx_dma_csr; int /*<<< orphan*/  tx_dma_csr; int /*<<< orphan*/  rxdescmem; int /*<<< orphan*/  rx_dma_desc; int /*<<< orphan*/  txdescmem; int /*<<< orphan*/  tx_dma_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGDMA_CTRLREG_RESET ; 
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  csrwr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sgdma_csroffs (int /*<<< orphan*/ ) ; 

void sgdma_reset(struct altera_tse_private *priv)
{
	/* Initialize descriptor memory to 0 */
	memset_io(priv->tx_dma_desc, 0, priv->txdescmem);
	memset_io(priv->rx_dma_desc, 0, priv->rxdescmem);

	csrwr32(SGDMA_CTRLREG_RESET, priv->tx_dma_csr, sgdma_csroffs(control));
	csrwr32(0, priv->tx_dma_csr, sgdma_csroffs(control));

	csrwr32(SGDMA_CTRLREG_RESET, priv->rx_dma_csr, sgdma_csroffs(control));
	csrwr32(0, priv->rx_dma_csr, sgdma_csroffs(control));
}