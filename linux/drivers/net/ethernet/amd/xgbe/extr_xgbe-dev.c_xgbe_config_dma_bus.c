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
struct xgbe_prv_data {int blen; int aal; int rd_osr_limit; int wr_osr_limit; TYPE_1__* vdata; } ;
struct TYPE_2__ {scalar_t__ rx_desc_prefetch; scalar_t__ tx_desc_prefetch; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAL ; 
 int /*<<< orphan*/  BLEN ; 
 int /*<<< orphan*/  DMA_RXEDMACR ; 
 int /*<<< orphan*/  DMA_SBMR ; 
 int /*<<< orphan*/  DMA_TXEDMACR ; 
 int /*<<< orphan*/  EAME ; 
 int /*<<< orphan*/  RDPS ; 
 int /*<<< orphan*/  RD_OSR_LMT ; 
 int /*<<< orphan*/  TDPS ; 
 int /*<<< orphan*/  UNDEF ; 
 int /*<<< orphan*/  WR_OSR_LMT ; 
 unsigned int XGMAC_IOREAD (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XGMAC_SET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgbe_config_dma_bus(struct xgbe_prv_data *pdata)
{
	unsigned int sbmr;

	sbmr = XGMAC_IOREAD(pdata, DMA_SBMR);

	/* Set enhanced addressing mode */
	XGMAC_SET_BITS(sbmr, DMA_SBMR, EAME, 1);

	/* Set the System Bus mode */
	XGMAC_SET_BITS(sbmr, DMA_SBMR, UNDEF, 1);
	XGMAC_SET_BITS(sbmr, DMA_SBMR, BLEN, pdata->blen >> 2);
	XGMAC_SET_BITS(sbmr, DMA_SBMR, AAL, pdata->aal);
	XGMAC_SET_BITS(sbmr, DMA_SBMR, RD_OSR_LMT, pdata->rd_osr_limit - 1);
	XGMAC_SET_BITS(sbmr, DMA_SBMR, WR_OSR_LMT, pdata->wr_osr_limit - 1);

	XGMAC_IOWRITE(pdata, DMA_SBMR, sbmr);

	/* Set descriptor fetching threshold */
	if (pdata->vdata->tx_desc_prefetch)
		XGMAC_IOWRITE_BITS(pdata, DMA_TXEDMACR, TDPS,
				   pdata->vdata->tx_desc_prefetch);

	if (pdata->vdata->rx_desc_prefetch)
		XGMAC_IOWRITE_BITS(pdata, DMA_RXEDMACR, RDPS,
				   pdata->vdata->rx_desc_prefetch);
}