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
typedef  int u32 ;
struct tsi721_dma_sts {int dummy; } ;
struct tsi721_dma_desc {int dummy; } ;
struct tsi721_device {int flags; TYPE_1__* msix; } ;
struct TYPE_5__ {TYPE_3__* device; } ;
struct tsi721_bdma_chan {size_t id; int bd_num; int sts_size; int /*<<< orphan*/ * sts_base; int /*<<< orphan*/  sts_phys; TYPE_2__ dchan; int /*<<< orphan*/ * bd_base; int /*<<< orphan*/  bd_phys; scalar_t__ regs; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ TSI721_DMAC_CTL ; 
 int /*<<< orphan*/  TSI721_DMAC_CTL_INIT ; 
 scalar_t__ TSI721_DMAC_STS ; 
 int TSI721_DMAC_STS_RUN ; 
 int TSI721_USING_MSIX ; 
 size_t TSI721_VECT_DMA0_DONE ; 
 size_t TSI721_VECT_DMA0_INT ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct tsi721_device* to_tsi721 (TYPE_3__*) ; 

__attribute__((used)) static int tsi721_bdma_ch_free(struct tsi721_bdma_chan *bdma_chan)
{
	u32 ch_stat;
#ifdef CONFIG_PCI_MSI
	struct tsi721_device *priv = to_tsi721(bdma_chan->dchan.device);
#endif

	if (!bdma_chan->bd_base)
		return 0;

	/* Check if DMA channel still running */
	ch_stat = ioread32(bdma_chan->regs + TSI721_DMAC_STS);
	if (ch_stat & TSI721_DMAC_STS_RUN)
		return -EFAULT;

	/* Put DMA channel into init state */
	iowrite32(TSI721_DMAC_CTL_INIT,	bdma_chan->regs + TSI721_DMAC_CTL);

#ifdef CONFIG_PCI_MSI
	if (priv->flags & TSI721_USING_MSIX) {
		free_irq(priv->msix[TSI721_VECT_DMA0_DONE +
				    bdma_chan->id].vector, (void *)bdma_chan);
		free_irq(priv->msix[TSI721_VECT_DMA0_INT +
				    bdma_chan->id].vector, (void *)bdma_chan);
	}
#endif /* CONFIG_PCI_MSI */

	/* Free space allocated for DMA descriptors */
	dma_free_coherent(bdma_chan->dchan.device->dev,
		(bdma_chan->bd_num + 1) * sizeof(struct tsi721_dma_desc),
		bdma_chan->bd_base, bdma_chan->bd_phys);
	bdma_chan->bd_base = NULL;

	/* Free space allocated for status FIFO */
	dma_free_coherent(bdma_chan->dchan.device->dev,
		bdma_chan->sts_size * sizeof(struct tsi721_dma_sts),
		bdma_chan->sts_base, bdma_chan->sts_phys);
	bdma_chan->sts_base = NULL;
	return 0;
}