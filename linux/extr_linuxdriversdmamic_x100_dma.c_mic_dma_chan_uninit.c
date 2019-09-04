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
 int /*<<< orphan*/  mic_dma_chan_destroy (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_cleanup (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_free_desc_ring (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_free_status_dest (struct mic_dma_chan*) ; 

__attribute__((used)) static inline void mic_dma_chan_uninit(struct mic_dma_chan *ch)
{
	mic_dma_chan_destroy(ch);
	mic_dma_cleanup(ch);
	mic_dma_free_status_dest(ch);
	mic_dma_free_desc_ring(ch);
}