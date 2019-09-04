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
struct fsldma_chan {int /*<<< orphan*/  feature; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSL_DMA_CHAN_PAUSE_EXT ; 

__attribute__((used)) static void fsl_chan_toggle_ext_pause(struct fsldma_chan *chan, int enable)
{
	if (enable)
		chan->feature |= FSL_DMA_CHAN_PAUSE_EXT;
	else
		chan->feature &= ~FSL_DMA_CHAN_PAUSE_EXT;
}