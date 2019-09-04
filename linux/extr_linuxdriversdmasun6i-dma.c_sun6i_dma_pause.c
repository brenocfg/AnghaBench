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
struct sun6i_vchan {int /*<<< orphan*/  node; int /*<<< orphan*/  vc; struct sun6i_pchan* phy; } ;
struct sun6i_pchan {scalar_t__ base; } ;
struct sun6i_dma_dev {int /*<<< orphan*/  lock; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ DMA_CHAN_PAUSE ; 
 int /*<<< orphan*/  DMA_CHAN_PAUSE_PAUSE ; 
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct sun6i_dma_dev* to_sun6i_dma_dev (int /*<<< orphan*/ ) ; 
 struct sun6i_vchan* to_sun6i_vchan (struct dma_chan*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sun6i_dma_pause(struct dma_chan *chan)
{
	struct sun6i_dma_dev *sdev = to_sun6i_dma_dev(chan->device);
	struct sun6i_vchan *vchan = to_sun6i_vchan(chan);
	struct sun6i_pchan *pchan = vchan->phy;

	dev_dbg(chan2dev(chan), "vchan %p: pause\n", &vchan->vc);

	if (pchan) {
		writel(DMA_CHAN_PAUSE_PAUSE,
		       pchan->base + DMA_CHAN_PAUSE);
	} else {
		spin_lock(&sdev->lock);
		list_del_init(&vchan->node);
		spin_unlock(&sdev->lock);
	}

	return 0;
}