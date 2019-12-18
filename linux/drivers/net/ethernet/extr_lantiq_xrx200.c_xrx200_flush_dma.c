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
struct TYPE_2__ {size_t desc; struct ltq_dma_desc* desc_base; } ;
struct xrx200_chan {TYPE_1__ dma; } ;
struct ltq_dma_desc {int ctl; } ;

/* Variables and functions */
 int LTQ_DESC_NUM ; 
 int LTQ_DMA_C ; 
 int LTQ_DMA_OWN ; 
 int LTQ_DMA_RX_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_IP_ALIGN ; 
 int XRX200_DMA_DATA_LEN ; 

__attribute__((used)) static void xrx200_flush_dma(struct xrx200_chan *ch)
{
	int i;

	for (i = 0; i < LTQ_DESC_NUM; i++) {
		struct ltq_dma_desc *desc = &ch->dma.desc_base[ch->dma.desc];

		if ((desc->ctl & (LTQ_DMA_OWN | LTQ_DMA_C)) != LTQ_DMA_C)
			break;

		desc->ctl = LTQ_DMA_OWN | LTQ_DMA_RX_OFFSET(NET_IP_ALIGN) |
			    XRX200_DMA_DATA_LEN;
		ch->dma.desc++;
		ch->dma.desc %= LTQ_DESC_NUM;
	}
}