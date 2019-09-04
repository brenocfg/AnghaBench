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
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int MIC_DMA_DESC_RX_SIZE ; 
 int mic_dma_chan_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mic_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int mic_dma_alloc_chan_resources(struct dma_chan *ch)
{
	int ret = mic_dma_chan_init(to_mic_dma_chan(ch));
	if (ret)
		return ret;
	return MIC_DMA_DESC_RX_SIZE;
}