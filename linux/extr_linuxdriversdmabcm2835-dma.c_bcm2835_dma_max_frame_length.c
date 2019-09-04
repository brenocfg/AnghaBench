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
struct bcm2835_chan {scalar_t__ is_lite_channel; } ;

/* Variables and functions */
 size_t MAX_DMA_LEN ; 
 size_t MAX_LITE_DMA_LEN ; 

__attribute__((used)) static inline size_t bcm2835_dma_max_frame_length(struct bcm2835_chan *c)
{
	/* lite and normal channels have different max frame length */
	return c->is_lite_channel ? MAX_LITE_DMA_LEN : MAX_DMA_LEN;
}