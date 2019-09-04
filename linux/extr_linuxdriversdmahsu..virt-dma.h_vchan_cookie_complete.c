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
struct TYPE_6__ {int /*<<< orphan*/  cookie; int /*<<< orphan*/  chan; } ;
struct virt_dma_desc {int /*<<< orphan*/  node; TYPE_3__ tx; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct virt_dma_chan {int /*<<< orphan*/  task; int /*<<< orphan*/  desc_completed; TYPE_2__ chan; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,struct virt_dma_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cookie_complete (TYPE_3__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct virt_dma_chan* to_virt_chan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vchan_cookie_complete(struct virt_dma_desc *vd)
{
	struct virt_dma_chan *vc = to_virt_chan(vd->tx.chan);
	dma_cookie_t cookie;

	cookie = vd->tx.cookie;
	dma_cookie_complete(&vd->tx);
	dev_vdbg(vc->chan.device->dev, "txd %p[%x]: marked complete\n",
		 vd, cookie);
	list_add_tail(&vd->node, &vc->desc_completed);

	tasklet_schedule(&vc->task);
}