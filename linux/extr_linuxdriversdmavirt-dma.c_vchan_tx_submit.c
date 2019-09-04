#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virt_dma_desc {int /*<<< orphan*/  node; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct virt_dma_chan {TYPE_2__ chan; int /*<<< orphan*/  lock; int /*<<< orphan*/  desc_submitted; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  chan; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct virt_dma_chan*,struct virt_dma_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cookie_assign (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct virt_dma_chan* to_virt_chan (int /*<<< orphan*/ ) ; 
 struct virt_dma_desc* to_virt_desc (struct dma_async_tx_descriptor*) ; 

dma_cookie_t vchan_tx_submit(struct dma_async_tx_descriptor *tx)
{
	struct virt_dma_chan *vc = to_virt_chan(tx->chan);
	struct virt_dma_desc *vd = to_virt_desc(tx);
	unsigned long flags;
	dma_cookie_t cookie;

	spin_lock_irqsave(&vc->lock, flags);
	cookie = dma_cookie_assign(tx);

	list_move_tail(&vd->node, &vc->desc_submitted);
	spin_unlock_irqrestore(&vc->lock, flags);

	dev_dbg(vc->chan.device->dev, "vchan %p: txd %p[%x]: submitted\n",
		vc, vd, cookie);

	return cookie;
}