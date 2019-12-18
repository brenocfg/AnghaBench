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
struct xlgmac_ring {int dma_desc_head_addr; unsigned int dma_desc_count; int /*<<< orphan*/  tx; scalar_t__ dirty; scalar_t__ cur; struct xlgmac_dma_desc* dma_desc_head; } ;
struct xlgmac_hw_ops {int /*<<< orphan*/  (* tx_desc_init ) (struct xlgmac_channel*) ;} ;
struct xlgmac_pdata {unsigned int channel_count; struct xlgmac_channel* channel_head; struct xlgmac_hw_ops hw_ops; } ;
struct xlgmac_dma_desc {int dummy; } ;
struct xlgmac_desc_data {int dma_desc_addr; struct xlgmac_dma_desc* dma_desc; } ;
struct xlgmac_channel {struct xlgmac_ring* tx_ring; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 struct xlgmac_desc_data* XLGMAC_GET_DESC_DATA (struct xlgmac_ring*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct xlgmac_channel*) ; 

__attribute__((used)) static void xlgmac_tx_desc_init(struct xlgmac_pdata *pdata)
{
	struct xlgmac_hw_ops *hw_ops = &pdata->hw_ops;
	struct xlgmac_desc_data *desc_data;
	struct xlgmac_dma_desc *dma_desc;
	struct xlgmac_channel *channel;
	struct xlgmac_ring *ring;
	dma_addr_t dma_desc_addr;
	unsigned int i, j;

	channel = pdata->channel_head;
	for (i = 0; i < pdata->channel_count; i++, channel++) {
		ring = channel->tx_ring;
		if (!ring)
			break;

		dma_desc = ring->dma_desc_head;
		dma_desc_addr = ring->dma_desc_head_addr;

		for (j = 0; j < ring->dma_desc_count; j++) {
			desc_data = XLGMAC_GET_DESC_DATA(ring, j);

			desc_data->dma_desc = dma_desc;
			desc_data->dma_desc_addr = dma_desc_addr;

			dma_desc++;
			dma_desc_addr += sizeof(struct xlgmac_dma_desc);
		}

		ring->cur = 0;
		ring->dirty = 0;
		memset(&ring->tx, 0, sizeof(ring->tx));

		hw_ops->tx_desc_init(channel);
	}
}