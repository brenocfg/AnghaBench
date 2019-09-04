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
struct dmatest_params {char* channel; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_chan_name (struct dma_chan*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool dmatest_match_channel(struct dmatest_params *params,
		struct dma_chan *chan)
{
	if (params->channel[0] == '\0')
		return true;
	return strcmp(dma_chan_name(chan), params->channel) == 0;
}