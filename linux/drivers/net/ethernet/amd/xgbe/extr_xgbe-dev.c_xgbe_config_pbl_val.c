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
struct xgbe_prv_data {unsigned int pbl; unsigned int channel_count; TYPE_1__** channel; } ;
struct TYPE_2__ {scalar_t__ rx_ring; scalar_t__ tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_CR ; 
 int /*<<< orphan*/  DMA_CH_RCR ; 
 int /*<<< orphan*/  DMA_CH_TCR ; 
 unsigned int DMA_PBL_X8_DISABLE ; 
 unsigned int DMA_PBL_X8_ENABLE ; 
 int /*<<< orphan*/  PBL ; 
 int /*<<< orphan*/  PBLX8 ; 
 int /*<<< orphan*/  XGMAC_DMA_IOWRITE_BITS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int xgbe_config_pbl_val(struct xgbe_prv_data *pdata)
{
	unsigned int pblx8, pbl;
	unsigned int i;

	pblx8 = DMA_PBL_X8_DISABLE;
	pbl = pdata->pbl;

	if (pdata->pbl > 32) {
		pblx8 = DMA_PBL_X8_ENABLE;
		pbl >>= 3;
	}

	for (i = 0; i < pdata->channel_count; i++) {
		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_CR, PBLX8,
				       pblx8);

		if (pdata->channel[i]->tx_ring)
			XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_TCR,
					       PBL, pbl);

		if (pdata->channel[i]->rx_ring)
			XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_RCR,
					       PBL, pbl);
	}

	return 0;
}