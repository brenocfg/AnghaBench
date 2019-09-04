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
struct mic_dma_chan {int dummy; } ;

/* Variables and functions */
 int mic_dma_alloc_desc_ring (struct mic_dma_chan*) ; 
 int mic_dma_alloc_status_dest (struct mic_dma_chan*) ; 
 int mic_dma_chan_setup (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_free_desc_ring (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_free_status_dest (struct mic_dma_chan*) ; 

__attribute__((used)) static int mic_dma_chan_init(struct mic_dma_chan *ch)
{
	int ret = mic_dma_alloc_desc_ring(ch);

	if (ret)
		goto ring_error;
	ret = mic_dma_alloc_status_dest(ch);
	if (ret)
		goto status_error;
	ret = mic_dma_chan_setup(ch);
	if (ret)
		goto chan_error;
	return ret;
chan_error:
	mic_dma_free_status_dest(ch);
status_error:
	mic_dma_free_desc_ring(ch);
ring_error:
	return ret;
}