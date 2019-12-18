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
typedef  unsigned int u32 ;
struct TYPE_2__ {unsigned int maxpacket; } ;
struct dwc2_hsotg_ep {int dir_in; unsigned int desc_count; scalar_t__ send_zlp; int /*<<< orphan*/  index; TYPE_1__ ep; } ;
struct dwc2_dma_desc {int status; unsigned int buf; } ;
typedef  unsigned int dma_addr_t ;

/* Variables and functions */
 int DEV_DMA_BUFF_STS_HBUSY ; 
 int DEV_DMA_BUFF_STS_HREADY ; 
 unsigned int DEV_DMA_BUFF_STS_MASK ; 
 int DEV_DMA_BUFF_STS_SHIFT ; 
 int DEV_DMA_IOC ; 
 int DEV_DMA_L ; 
 unsigned int DEV_DMA_NBYTES_SHIFT ; 
 int DEV_DMA_SHORT ; 
 unsigned int dwc2_gadget_get_desc_params (struct dwc2_hsotg_ep*,unsigned int*) ; 

__attribute__((used)) static void dwc2_gadget_fill_nonisoc_xfer_ddma_one(struct dwc2_hsotg_ep *hs_ep,
						 struct dwc2_dma_desc **desc,
						 dma_addr_t dma_buff,
						 unsigned int len,
						 bool true_last)
{
	int dir_in = hs_ep->dir_in;
	u32 mps = hs_ep->ep.maxpacket;
	u32 maxsize = 0;
	u32 offset = 0;
	u32 mask = 0;
	int i;

	maxsize = dwc2_gadget_get_desc_params(hs_ep, &mask);

	hs_ep->desc_count = (len / maxsize) +
				((len % maxsize) ? 1 : 0);
	if (len == 0)
		hs_ep->desc_count = 1;

	for (i = 0; i < hs_ep->desc_count; ++i) {
		(*desc)->status = 0;
		(*desc)->status |= (DEV_DMA_BUFF_STS_HBUSY
				 << DEV_DMA_BUFF_STS_SHIFT);

		if (len > maxsize) {
			if (!hs_ep->index && !dir_in)
				(*desc)->status |= (DEV_DMA_L | DEV_DMA_IOC);

			(*desc)->status |=
				maxsize << DEV_DMA_NBYTES_SHIFT & mask;
			(*desc)->buf = dma_buff + offset;

			len -= maxsize;
			offset += maxsize;
		} else {
			if (true_last)
				(*desc)->status |= (DEV_DMA_L | DEV_DMA_IOC);

			if (dir_in)
				(*desc)->status |= (len % mps) ? DEV_DMA_SHORT :
					((hs_ep->send_zlp && true_last) ?
					DEV_DMA_SHORT : 0);

			(*desc)->status |=
				len << DEV_DMA_NBYTES_SHIFT & mask;
			(*desc)->buf = dma_buff + offset;
		}

		(*desc)->status &= ~DEV_DMA_BUFF_STS_MASK;
		(*desc)->status |= (DEV_DMA_BUFF_STS_HREADY
				 << DEV_DMA_BUFF_STS_SHIFT);
		(*desc)++;
	}
}