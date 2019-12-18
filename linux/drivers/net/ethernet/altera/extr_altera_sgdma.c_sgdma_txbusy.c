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
struct altera_tse_private {int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_dma_csr; } ;

/* Variables and functions */
 int SGDMA_STSREG_BUSY ; 
 int csrrd32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sgdma_csroffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sgdma_txbusy(struct altera_tse_private *priv)
{
	int delay = 0;

	/* if DMA is busy, wait for current transactino to finish */
	while ((csrrd32(priv->tx_dma_csr, sgdma_csroffs(status))
		& SGDMA_STSREG_BUSY) && (delay++ < 100))
		udelay(1);

	if (csrrd32(priv->tx_dma_csr, sgdma_csroffs(status))
	    & SGDMA_STSREG_BUSY) {
		netdev_err(priv->dev, "timeout waiting for tx dma\n");
		return 1;
	}
	return 0;
}