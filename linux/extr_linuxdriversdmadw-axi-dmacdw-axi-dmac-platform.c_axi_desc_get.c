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
struct dw_axi_dma {int /*<<< orphan*/  desc_pool; } ;
struct TYPE_4__ {int /*<<< orphan*/  phys; } ;
struct TYPE_5__ {TYPE_1__ tx; } ;
struct axi_dma_desc {struct axi_dma_chan* chan; TYPE_2__ vd; int /*<<< orphan*/  xfer_list; } ;
struct axi_dma_chan {int /*<<< orphan*/  descs_allocated; TYPE_3__* chip; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {struct dw_axi_dma* dw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  axi_chan_name (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  chan2dev (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct axi_dma_desc* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct axi_dma_desc *axi_desc_get(struct axi_dma_chan *chan)
{
	struct dw_axi_dma *dw = chan->chip->dw;
	struct axi_dma_desc *desc;
	dma_addr_t phys;

	desc = dma_pool_zalloc(dw->desc_pool, GFP_NOWAIT, &phys);
	if (unlikely(!desc)) {
		dev_err(chan2dev(chan), "%s: not enough descriptors available\n",
			axi_chan_name(chan));
		return NULL;
	}

	atomic_inc(&chan->descs_allocated);
	INIT_LIST_HEAD(&desc->xfer_list);
	desc->vd.tx.phys = phys;
	desc->chan = chan;

	return desc;
}