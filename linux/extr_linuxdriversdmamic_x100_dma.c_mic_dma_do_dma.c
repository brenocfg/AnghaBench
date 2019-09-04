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
struct mic_dma_chan {size_t head; int /*<<< orphan*/  status_dest_micpa; int /*<<< orphan*/ * desc_ring; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DMA_PREP_FENCE ; 
 int DMA_PREP_INTERRUPT ; 
 int ENOMEM ; 
 int mic_dma_avail_desc_ring_space (struct mic_dma_chan*,int) ; 
 int /*<<< orphan*/  mic_dma_hw_ring_inc_head (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_prep_status_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mic_dma_prog_intr (struct mic_dma_chan*) ; 
 int mic_dma_prog_memcpy_desc (struct mic_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int mic_dma_do_dma(struct mic_dma_chan *ch, int flags, dma_addr_t src,
			  dma_addr_t dst, size_t len)
{
	if (len && -ENOMEM == mic_dma_prog_memcpy_desc(ch, src, dst, len)) {
		return -ENOMEM;
	} else {
		/* 3 is the maximum number of status descriptors */
		int ret = mic_dma_avail_desc_ring_space(ch, 3);

		if (ret < 0)
			return ret;
	}

	/* Above mic_dma_prog_memcpy_desc() makes sure we have enough space */
	if (flags & DMA_PREP_FENCE) {
		mic_dma_prep_status_desc(&ch->desc_ring[ch->head], 0,
					 ch->status_dest_micpa, false);
		mic_dma_hw_ring_inc_head(ch);
	}

	if (flags & DMA_PREP_INTERRUPT)
		mic_dma_prog_intr(ch);

	return 0;
}