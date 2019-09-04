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
typedef  int /*<<< orphan*/  dma_t ;

/* Variables and functions */
 unsigned int MAX_DMA_CHANNELS ; 
 int /*<<< orphan*/ ** dma_chan ; 

__attribute__((used)) static inline dma_t *dma_channel(unsigned int chan)
{
	if (chan >= MAX_DMA_CHANNELS)
		return NULL;

	return dma_chan[chan];
}