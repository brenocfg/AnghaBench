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
struct xgbe_prv_data {unsigned int channel_count; int /*<<< orphan*/  rx_riwt; TYPE_1__** channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_RIWT ; 
 int /*<<< orphan*/  RWT ; 
 int /*<<< orphan*/  XGMAC_DMA_IOWRITE_BITS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgbe_config_rx_coalesce(struct xgbe_prv_data *pdata)
{
	unsigned int i;

	for (i = 0; i < pdata->channel_count; i++) {
		if (!pdata->channel[i]->rx_ring)
			break;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_RIWT, RWT,
				       pdata->rx_riwt);
	}

	return 0;
}