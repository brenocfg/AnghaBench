#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tsi721_device {int flags; TYPE_1__* pdev; TYPE_3__* msix; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct tsi721_bdma_chan {size_t id; TYPE_2__ dchan; } ;
struct TYPE_6__ {int /*<<< orphan*/  vector; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int TSI721_USING_MSIX ; 
 size_t TSI721_VECT_DMA0_DONE ; 
 size_t TSI721_VECT_DMA0_INT ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 struct tsi721_device* to_tsi721 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsi721_sync_dma_irq(struct tsi721_bdma_chan *bdma_chan)
{
	struct tsi721_device *priv = to_tsi721(bdma_chan->dchan.device);

#ifdef CONFIG_PCI_MSI
	if (priv->flags & TSI721_USING_MSIX) {
		synchronize_irq(priv->msix[TSI721_VECT_DMA0_DONE +
					   bdma_chan->id].vector);
		synchronize_irq(priv->msix[TSI721_VECT_DMA0_INT +
					   bdma_chan->id].vector);
	} else
#endif
	synchronize_irq(priv->pdev->irq);
}