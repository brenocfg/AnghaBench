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
struct sdma_engine {int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  clk_ipg; } ;
struct sdma_channel {scalar_t__ event_id1; scalar_t__ event_id0; struct sdma_engine* sdma; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_channel_synchronize (struct dma_chan*) ; 
 int /*<<< orphan*/  sdma_disable_channel_async (struct dma_chan*) ; 
 int /*<<< orphan*/  sdma_event_disable (struct sdma_channel*,scalar_t__) ; 
 int /*<<< orphan*/  sdma_set_channel_priority (struct sdma_channel*,int /*<<< orphan*/ ) ; 
 struct sdma_channel* to_sdma_chan (struct dma_chan*) ; 

__attribute__((used)) static void sdma_free_chan_resources(struct dma_chan *chan)
{
	struct sdma_channel *sdmac = to_sdma_chan(chan);
	struct sdma_engine *sdma = sdmac->sdma;

	sdma_disable_channel_async(chan);

	sdma_channel_synchronize(chan);

	if (sdmac->event_id0)
		sdma_event_disable(sdmac, sdmac->event_id0);
	if (sdmac->event_id1)
		sdma_event_disable(sdmac, sdmac->event_id1);

	sdmac->event_id0 = 0;
	sdmac->event_id1 = 0;

	sdma_set_channel_priority(sdmac, 0);

	clk_disable(sdma->clk_ipg);
	clk_disable(sdma->clk_ahb);
}