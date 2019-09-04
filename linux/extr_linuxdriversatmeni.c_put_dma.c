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
typedef  int u32 ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,unsigned long,int,...) ; 
 int /*<<< orphan*/  EVENT (char*,unsigned long,int) ; 
 int MID_DMA_CHAN_SHIFT ; 
 int MID_DMA_COUNT_SHIFT ; 
 int MID_DT_BYTE ; 
 int MID_DT_WORD ; 

__attribute__((used)) static inline void put_dma(int chan,u32 *dma,int *j,dma_addr_t paddr,
    u32 size)
{
	u32 init,words;

	DPRINTK("put_dma: 0x%lx+0x%x\n",(unsigned long) paddr,size);
	EVENT("put_dma: 0x%lx+0x%lx\n",(unsigned long) paddr,size);
#if 0 /* don't complain anymore */
	if (paddr & 3)
		printk(KERN_ERR "put_dma: unaligned addr (0x%lx)\n",paddr);
	if (size & 3)
		printk(KERN_ERR "put_dma: unaligned size (0x%lx)\n",size);
#endif
	if (paddr & 3) {
		init = 4-(paddr & 3);
		if (init > size || size < 7) init = size;
		DPRINTK("put_dma: %lx DMA: %d/%d bytes\n",
		    (unsigned long) paddr,init,size);
		dma[(*j)++] = MID_DT_BYTE | (init << MID_DMA_COUNT_SHIFT) |
		    (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
		paddr += init;
		size -= init;
	}
	words = size >> 2;
	size &= 3;
	if (words && (paddr & 31)) {
		init = 8-((paddr & 31) >> 2);
		if (init > words) init = words;
		DPRINTK("put_dma: %lx DMA: %d/%d words\n",
		    (unsigned long) paddr,init,words);
		dma[(*j)++] = MID_DT_WORD | (init << MID_DMA_COUNT_SHIFT) |
		    (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
		paddr += init << 2;
		words -= init;
	}
#ifdef CONFIG_ATM_ENI_BURST_TX_16W /* may work with some PCI chipsets ... */
	if (words & ~15) {
		DPRINTK("put_dma: %lx DMA: %d*16/%d words\n",
		    (unsigned long) paddr,words >> 4,words);
		dma[(*j)++] = MID_DT_16W | ((words >> 4) << MID_DMA_COUNT_SHIFT)
		    | (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
		paddr += (words & ~15) << 2;
		words &= 15;
	}
#endif
#ifdef CONFIG_ATM_ENI_BURST_TX_8W /* recommended */
	if (words & ~7) {
		DPRINTK("put_dma: %lx DMA: %d*8/%d words\n",
		    (unsigned long) paddr,words >> 3,words);
		dma[(*j)++] = MID_DT_8W | ((words >> 3) << MID_DMA_COUNT_SHIFT)
		    | (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
		paddr += (words & ~7) << 2;
		words &= 7;
	}
#endif
#ifdef CONFIG_ATM_ENI_BURST_TX_4W /* probably useless if TX_8W or TX_16W */
	if (words & ~3) {
		DPRINTK("put_dma: %lx DMA: %d*4/%d words\n",
		    (unsigned long) paddr,words >> 2,words);
		dma[(*j)++] = MID_DT_4W | ((words >> 2) << MID_DMA_COUNT_SHIFT)
		    | (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
		paddr += (words & ~3) << 2;
		words &= 3;
	}
#endif
#ifdef CONFIG_ATM_ENI_BURST_TX_2W /* probably useless if TX_4W, TX_8W, ... */
	if (words & ~1) {
		DPRINTK("put_dma: %lx DMA: %d*2/%d words\n",
		    (unsigned long) paddr,words >> 1,words);
		dma[(*j)++] = MID_DT_2W | ((words >> 1) << MID_DMA_COUNT_SHIFT)
		    | (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
		paddr += (words & ~1) << 2;
		words &= 1;
	}
#endif
	if (words) {
		DPRINTK("put_dma: %lx DMA: %d words\n",(unsigned long) paddr,
		    words);
		dma[(*j)++] = MID_DT_WORD | (words << MID_DMA_COUNT_SHIFT) |
		    (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
		paddr += words << 2;
	}
	if (size) {
		DPRINTK("put_dma: %lx DMA: %d bytes\n",(unsigned long) paddr,
		    size);
		dma[(*j)++] = MID_DT_BYTE | (size << MID_DMA_COUNT_SHIFT) |
		    (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
	}
}