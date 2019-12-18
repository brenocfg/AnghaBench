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
struct dma_chan {long chan_id; } ;

/* Variables and functions */

__attribute__((used)) static bool ks8842_dma_filter_fn(struct dma_chan *chan, void *filter_param)
{
	return chan->chan_id == (long)filter_param;
}