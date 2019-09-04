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
struct virt_dma_desc {int /*<<< orphan*/  node; } ;
struct virt_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  desc_completed; } ;
struct sun6i_vchan {int cyclic; struct virt_dma_chan vc; struct sun6i_pchan* phy; int /*<<< orphan*/  node; } ;
struct sun6i_pchan {int /*<<< orphan*/ * done; TYPE_1__* desc; int /*<<< orphan*/ * vchan; scalar_t__ base; } ;
struct sun6i_dma_dev {int /*<<< orphan*/  lock; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {struct virt_dma_desc vd; } ;

/* Variables and functions */
 scalar_t__ DMA_CHAN_ENABLE ; 
 int /*<<< orphan*/  DMA_CHAN_ENABLE_STOP ; 
 scalar_t__ DMA_CHAN_PAUSE ; 
 int /*<<< orphan*/  DMA_CHAN_PAUSE_RESUME ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct sun6i_dma_dev* to_sun6i_dma_dev (int /*<<< orphan*/ ) ; 
 struct sun6i_vchan* to_sun6i_vchan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (struct virt_dma_chan*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (struct virt_dma_chan*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sun6i_dma_terminate_all(struct dma_chan *chan)
{
	struct sun6i_dma_dev *sdev = to_sun6i_dma_dev(chan->device);
	struct sun6i_vchan *vchan = to_sun6i_vchan(chan);
	struct sun6i_pchan *pchan = vchan->phy;
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock(&sdev->lock);
	list_del_init(&vchan->node);
	spin_unlock(&sdev->lock);

	spin_lock_irqsave(&vchan->vc.lock, flags);

	if (vchan->cyclic) {
		vchan->cyclic = false;
		if (pchan && pchan->desc) {
			struct virt_dma_desc *vd = &pchan->desc->vd;
			struct virt_dma_chan *vc = &vchan->vc;

			list_add_tail(&vd->node, &vc->desc_completed);
		}
	}

	vchan_get_all_descriptors(&vchan->vc, &head);

	if (pchan) {
		writel(DMA_CHAN_ENABLE_STOP, pchan->base + DMA_CHAN_ENABLE);
		writel(DMA_CHAN_PAUSE_RESUME, pchan->base + DMA_CHAN_PAUSE);

		vchan->phy = NULL;
		pchan->vchan = NULL;
		pchan->desc = NULL;
		pchan->done = NULL;
	}

	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	vchan_dma_desc_free_list(&vchan->vc, &head);

	return 0;
}