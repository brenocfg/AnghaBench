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
typedef  int /*<<< orphan*/  u32 ;
struct fsldma_chan {int feature; } ;

/* Variables and functions */
 int FSL_DMA_CHAN_PAUSE_EXT ; 
 int FSL_DMA_CHAN_START_EXT ; 
 int /*<<< orphan*/  FSL_DMA_MR_CS ; 
 int /*<<< orphan*/  FSL_DMA_MR_EMP_EN ; 
 int /*<<< orphan*/  FSL_DMA_MR_EMS_EN ; 
 int /*<<< orphan*/  get_mr (struct fsldma_chan*) ; 
 int /*<<< orphan*/  set_bcr (struct fsldma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mr (struct fsldma_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dma_start(struct fsldma_chan *chan)
{
	u32 mode;

	mode = get_mr(chan);

	if (chan->feature & FSL_DMA_CHAN_PAUSE_EXT) {
		set_bcr(chan, 0);
		mode |= FSL_DMA_MR_EMP_EN;
	} else {
		mode &= ~FSL_DMA_MR_EMP_EN;
	}

	if (chan->feature & FSL_DMA_CHAN_START_EXT) {
		mode |= FSL_DMA_MR_EMS_EN;
	} else {
		mode &= ~FSL_DMA_MR_EMS_EN;
		mode |= FSL_DMA_MR_CS;
	}

	set_mr(chan, mode);
}