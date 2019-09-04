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
struct pl08x_dma_chan {void* cd; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct pl08x_dma_chan* to_pl08x_chan (struct dma_chan*) ; 

__attribute__((used)) static bool pl08x_filter_fn(struct dma_chan *chan, void *chan_id)
{
	struct pl08x_dma_chan *plchan = to_pl08x_chan(chan);

	return plchan->cd == chan_id;
}