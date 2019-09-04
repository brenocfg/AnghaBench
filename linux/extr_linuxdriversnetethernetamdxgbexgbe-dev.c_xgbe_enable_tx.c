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
struct xgbe_prv_data {unsigned int channel_count; unsigned int tx_q_count; TYPE_1__** channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_TCR ; 
 int /*<<< orphan*/  MAC_TCR ; 
 int /*<<< orphan*/  MTL_Q_ENABLED ; 
 int /*<<< orphan*/  MTL_Q_TQOMR ; 
 int /*<<< orphan*/  ST ; 
 int /*<<< orphan*/  TE ; 
 int /*<<< orphan*/  TXQEN ; 
 int /*<<< orphan*/  XGMAC_DMA_IOWRITE_BITS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XGMAC_MTL_IOWRITE_BITS (struct xgbe_prv_data*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_enable_tx(struct xgbe_prv_data *pdata)
{
	unsigned int i;

	/* Enable each Tx DMA channel */
	for (i = 0; i < pdata->channel_count; i++) {
		if (!pdata->channel[i]->tx_ring)
			break;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_TCR, ST, 1);
	}

	/* Enable each Tx queue */
	for (i = 0; i < pdata->tx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_TQOMR, TXQEN,
				       MTL_Q_ENABLED);

	/* Enable MAC Tx */
	XGMAC_IOWRITE_BITS(pdata, MAC_TCR, TE, 1);
}