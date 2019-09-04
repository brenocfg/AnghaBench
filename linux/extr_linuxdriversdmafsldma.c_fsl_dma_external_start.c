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
struct fsldma_chan {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  fsl_chan_toggle_ext_start (struct fsldma_chan*,int) ; 
 struct fsldma_chan* to_fsl_chan (struct dma_chan*) ; 

int fsl_dma_external_start(struct dma_chan *dchan, int enable)
{
	struct fsldma_chan *chan;

	if (!dchan)
		return -EINVAL;

	chan = to_fsl_chan(dchan);

	fsl_chan_toggle_ext_start(chan, enable);
	return 0;
}