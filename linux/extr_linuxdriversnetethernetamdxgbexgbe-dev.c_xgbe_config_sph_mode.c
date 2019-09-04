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
struct xgbe_prv_data {unsigned int channel_count; TYPE_1__** channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_CR ; 
 int /*<<< orphan*/  HDSMS ; 
 int /*<<< orphan*/  MAC_RCR ; 
 int /*<<< orphan*/  SPH ; 
 int /*<<< orphan*/  XGBE_SPH_HDSMS_SIZE ; 
 int /*<<< orphan*/  XGMAC_DMA_IOWRITE_BITS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_config_sph_mode(struct xgbe_prv_data *pdata)
{
	unsigned int i;

	for (i = 0; i < pdata->channel_count; i++) {
		if (!pdata->channel[i]->rx_ring)
			break;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_CR, SPH, 1);
	}

	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, HDSMS, XGBE_SPH_HDSMS_SIZE);
}