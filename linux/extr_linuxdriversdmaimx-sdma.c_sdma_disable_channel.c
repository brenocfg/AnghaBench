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
struct sdma_engine {scalar_t__ regs; } ;
struct sdma_channel {int channel; int /*<<< orphan*/  status; struct sdma_engine* sdma; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  DMA_ERROR ; 
 scalar_t__ SDMA_H_STATSTOP ; 
 struct sdma_channel* to_sdma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sdma_disable_channel(struct dma_chan *chan)
{
	struct sdma_channel *sdmac = to_sdma_chan(chan);
	struct sdma_engine *sdma = sdmac->sdma;
	int channel = sdmac->channel;

	writel_relaxed(BIT(channel), sdma->regs + SDMA_H_STATSTOP);
	sdmac->status = DMA_ERROR;

	return 0;
}