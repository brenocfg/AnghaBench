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
struct virt_dma_desc {int /*<<< orphan*/  tx; int /*<<< orphan*/  node; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {TYPE_1__ chan; } ;
struct sun6i_vchan {int irq_type; scalar_t__ cyclic; struct sun6i_pchan* phy; TYPE_2__ vc; } ;
struct sun6i_pchan {int idx; scalar_t__ base; TYPE_3__* desc; int /*<<< orphan*/ * done; } ;
struct sun6i_dma_dev {scalar_t__ base; } ;
struct TYPE_6__ {int p_lli; int /*<<< orphan*/  v_lli; } ;

/* Variables and functions */
 scalar_t__ DMA_CHAN_ENABLE ; 
 int DMA_CHAN_ENABLE_START ; 
 scalar_t__ DMA_CHAN_LLI_ADDR ; 
 int DMA_IRQ_CHAN_NR ; 
 int DMA_IRQ_CHAN_WIDTH ; 
 scalar_t__ DMA_IRQ_EN (int) ; 
 int DMA_IRQ_HALF ; 
 int DMA_IRQ_PKG ; 
 int DMA_IRQ_QUEUE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sun6i_dma_dump_chan_regs (struct sun6i_dma_dev*,struct sun6i_pchan*) ; 
 int /*<<< orphan*/  sun6i_dma_dump_com_regs (struct sun6i_dma_dev*) ; 
 int /*<<< orphan*/  sun6i_dma_dump_lli (struct sun6i_vchan*,int /*<<< orphan*/ ) ; 
 TYPE_3__* to_sun6i_desc (int /*<<< orphan*/ *) ; 
 struct sun6i_dma_dev* to_sun6i_dma_dev (int /*<<< orphan*/ ) ; 
 struct virt_dma_desc* vchan_next_desc (TYPE_2__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sun6i_dma_start_desc(struct sun6i_vchan *vchan)
{
	struct sun6i_dma_dev *sdev = to_sun6i_dma_dev(vchan->vc.chan.device);
	struct virt_dma_desc *desc = vchan_next_desc(&vchan->vc);
	struct sun6i_pchan *pchan = vchan->phy;
	u32 irq_val, irq_reg, irq_offset;

	if (!pchan)
		return -EAGAIN;

	if (!desc) {
		pchan->desc = NULL;
		pchan->done = NULL;
		return -EAGAIN;
	}

	list_del(&desc->node);

	pchan->desc = to_sun6i_desc(&desc->tx);
	pchan->done = NULL;

	sun6i_dma_dump_lli(vchan, pchan->desc->v_lli);

	irq_reg = pchan->idx / DMA_IRQ_CHAN_NR;
	irq_offset = pchan->idx % DMA_IRQ_CHAN_NR;

	vchan->irq_type = vchan->cyclic ? DMA_IRQ_PKG : DMA_IRQ_QUEUE;

	irq_val = readl(sdev->base + DMA_IRQ_EN(irq_reg));
	irq_val &= ~((DMA_IRQ_HALF | DMA_IRQ_PKG | DMA_IRQ_QUEUE) <<
			(irq_offset * DMA_IRQ_CHAN_WIDTH));
	irq_val |= vchan->irq_type << (irq_offset * DMA_IRQ_CHAN_WIDTH);
	writel(irq_val, sdev->base + DMA_IRQ_EN(irq_reg));

	writel(pchan->desc->p_lli, pchan->base + DMA_CHAN_LLI_ADDR);
	writel(DMA_CHAN_ENABLE_START, pchan->base + DMA_CHAN_ENABLE);

	sun6i_dma_dump_com_regs(sdev);
	sun6i_dma_dump_chan_regs(sdev, pchan);

	return 0;
}