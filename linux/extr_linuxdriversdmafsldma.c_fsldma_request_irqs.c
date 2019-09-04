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
 int ENODEV ; 
 int FSL_DMA_MAX_CHANS_PER_DEVICE ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  chan_dbg (struct fsldma_device*,char*) ; 
 int /*<<< orphan*/  chan_err (struct fsldma_device*,char*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct fsldma_device*) ; 
 int /*<<< orphan*/  fsldma_chan_irq ; 
 int /*<<< orphan*/  fsldma_ctrl_irq ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct fsldma_device*) ; 

__attribute__((used)) static int fsldma_request_irqs(struct fsldma_device *fdev)
{
	struct fsldma_chan *chan;
	int ret;
	int i;

	/* if we have a per-controller IRQ, use that */
	if (fdev->irq) {
		dev_dbg(fdev->dev, "request per-controller IRQ\n");
		ret = request_irq(fdev->irq, fsldma_ctrl_irq, IRQF_SHARED,
				  "fsldma-controller", fdev);
		return ret;
	}

	/* no per-controller IRQ, use the per-channel IRQs */
	for (i = 0; i < FSL_DMA_MAX_CHANS_PER_DEVICE; i++) {
		chan = fdev->chan[i];
		if (!chan)
			continue;

		if (!chan->irq) {
			chan_err(chan, "interrupts property missing in device tree\n");
			ret = -ENODEV;
			goto out_unwind;
		}

		chan_dbg(chan, "request per-channel IRQ\n");
		ret = request_irq(chan->irq, fsldma_chan_irq, IRQF_SHARED,
				  "fsldma-chan", chan);
		if (ret) {
			chan_err(chan, "unable to request per-channel IRQ\n");
			goto out_unwind;
		}
	}

	return 0;

out_unwind:
	for (/* none */; i >= 0; i--) {
		chan = fdev->chan[i];
		if (!chan)
			continue;

		if (!chan->irq)
			continue;

		free_irq(chan->irq, chan);
	}

	return ret;
}