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
struct xlgmac_ring {unsigned int dma_desc_count; } ;
struct xlgmac_desc_ops {int /*<<< orphan*/  (* unmap_desc_data ) (struct xlgmac_pdata*,struct xlgmac_desc_data*) ;} ;
struct xlgmac_pdata {unsigned int channel_count; struct xlgmac_channel* channel_head; struct xlgmac_desc_ops desc_ops; } ;
struct xlgmac_desc_data {int dummy; } ;
struct xlgmac_channel {struct xlgmac_ring* tx_ring; } ;

/* Variables and functions */
 struct xlgmac_desc_data* XLGMAC_GET_DESC_DATA (struct xlgmac_ring*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct xlgmac_pdata*,struct xlgmac_desc_data*) ; 

__attribute__((used)) static void xlgmac_free_tx_data(struct xlgmac_pdata *pdata)
{
	struct xlgmac_desc_ops *desc_ops = &pdata->desc_ops;
	struct xlgmac_desc_data *desc_data;
	struct xlgmac_channel *channel;
	struct xlgmac_ring *ring;
	unsigned int i, j;

	channel = pdata->channel_head;
	for (i = 0; i < pdata->channel_count; i++, channel++) {
		ring = channel->tx_ring;
		if (!ring)
			break;

		for (j = 0; j < ring->dma_desc_count; j++) {
			desc_data = XLGMAC_GET_DESC_DATA(ring, j);
			desc_ops->unmap_desc_data(pdata, desc_data);
		}
	}
}