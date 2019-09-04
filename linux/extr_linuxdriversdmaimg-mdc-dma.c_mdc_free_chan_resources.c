#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mdc_dma {TYPE_1__* soc; } ;
struct mdc_chan {struct mdc_dma* mdma; } ;
struct dma_chan {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_chan ) (struct mdc_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mdc_terminate_all (struct dma_chan*) ; 
 struct device* mdma2dev (struct mdc_dma*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct mdc_chan*) ; 
 struct mdc_chan* to_mdc_chan (struct dma_chan*) ; 

__attribute__((used)) static void mdc_free_chan_resources(struct dma_chan *chan)
{
	struct mdc_chan *mchan = to_mdc_chan(chan);
	struct mdc_dma *mdma = mchan->mdma;
	struct device *dev = mdma2dev(mdma);

	mdc_terminate_all(chan);
	mdma->soc->disable_chan(mchan);
	pm_runtime_put(dev);
}