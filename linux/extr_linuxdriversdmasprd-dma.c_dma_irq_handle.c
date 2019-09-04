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
typedef  int u32 ;
struct sprd_dma_dev {struct sprd_dma_chn* channels; scalar_t__ glb_base; } ;
struct sprd_dma_desc {int /*<<< orphan*/  vd; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct sprd_dma_chn {TYPE_1__ vc; struct sprd_dma_desc* cur_desc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum sprd_dma_req_mode { ____Placeholder_sprd_dma_req_mode } sprd_dma_req_mode ;
typedef  enum sprd_dma_int_type { ____Placeholder_sprd_dma_int_type } sprd_dma_int_type ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SPRD_DMA_GLB_INT_MSK_STS ; 
 int __ffs (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sprd_dma_check_trans_done (struct sprd_dma_desc*,int,int) ; 
 int /*<<< orphan*/  sprd_dma_clear_int (struct sprd_dma_chn*) ; 
 int sprd_dma_get_int_type (struct sprd_dma_chn*) ; 
 int sprd_dma_get_req_type (struct sprd_dma_chn*) ; 
 int /*<<< orphan*/  sprd_dma_start (struct sprd_dma_chn*) ; 
 int /*<<< orphan*/  vchan_cookie_complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t dma_irq_handle(int irq, void *dev_id)
{
	struct sprd_dma_dev *sdev = (struct sprd_dma_dev *)dev_id;
	u32 irq_status = readl(sdev->glb_base + SPRD_DMA_GLB_INT_MSK_STS);
	struct sprd_dma_chn *schan;
	struct sprd_dma_desc *sdesc;
	enum sprd_dma_req_mode req_type;
	enum sprd_dma_int_type int_type;
	bool trans_done = false;
	u32 i;

	while (irq_status) {
		i = __ffs(irq_status);
		irq_status &= (irq_status - 1);
		schan = &sdev->channels[i];

		spin_lock(&schan->vc.lock);
		int_type = sprd_dma_get_int_type(schan);
		req_type = sprd_dma_get_req_type(schan);
		sprd_dma_clear_int(schan);

		sdesc = schan->cur_desc;

		/* Check if the dma request descriptor is done. */
		trans_done = sprd_dma_check_trans_done(sdesc, int_type,
						       req_type);
		if (trans_done == true) {
			vchan_cookie_complete(&sdesc->vd);
			schan->cur_desc = NULL;
			sprd_dma_start(schan);
		}
		spin_unlock(&schan->vc.lock);
	}

	return IRQ_HANDLED;
}