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
struct sdma_channel {int /*<<< orphan*/  terminate_worker; scalar_t__ desc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdma_disable_channel (struct dma_chan*) ; 
 struct sdma_channel* to_sdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int sdma_disable_channel_async(struct dma_chan *chan)
{
	struct sdma_channel *sdmac = to_sdma_chan(chan);

	sdma_disable_channel(chan);

	if (sdmac->desc)
		schedule_work(&sdmac->terminate_worker);

	return 0;
}