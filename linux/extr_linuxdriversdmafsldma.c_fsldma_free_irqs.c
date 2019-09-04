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
struct fsldma_device {scalar_t__ irq; struct fsldma_device** chan; int /*<<< orphan*/  dev; } ;
struct fsldma_chan {scalar_t__ irq; struct fsldma_chan** chan; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FSL_DMA_MAX_CHANS_PER_DEVICE ; 
 int /*<<< orphan*/  chan_dbg (struct fsldma_device*,char*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct fsldma_device*) ; 

__attribute__((used)) static void fsldma_free_irqs(struct fsldma_device *fdev)
{
	struct fsldma_chan *chan;
	int i;

	if (fdev->irq) {
		dev_dbg(fdev->dev, "free per-controller IRQ\n");
		free_irq(fdev->irq, fdev);
		return;
	}

	for (i = 0; i < FSL_DMA_MAX_CHANS_PER_DEVICE; i++) {
		chan = fdev->chan[i];
		if (chan && chan->irq) {
			chan_dbg(chan, "free per-channel IRQ\n");
			free_irq(chan->irq, chan);
		}
	}
}