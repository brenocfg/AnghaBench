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
struct TYPE_2__ {int /*<<< orphan*/  cookie; } ;
struct virt_dma_desc {TYPE_1__ tx; } ;
struct axi_dma_desc {int dummy; } ;
struct axi_dma_chan {int /*<<< orphan*/  vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  axi_chan_block_xfer_start (struct axi_dma_chan*,struct axi_dma_desc*) ; 
 int /*<<< orphan*/  axi_chan_name (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  chan2dev (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 
 struct axi_dma_desc* vd_to_axi_desc (struct virt_dma_desc*) ; 

__attribute__((used)) static void axi_chan_start_first_queued(struct axi_dma_chan *chan)
{
	struct axi_dma_desc *desc;
	struct virt_dma_desc *vd;

	vd = vchan_next_desc(&chan->vc);
	if (!vd)
		return;

	desc = vd_to_axi_desc(vd);
	dev_vdbg(chan2dev(chan), "%s: started %u\n", axi_chan_name(chan),
		vd->tx.cookie);
	axi_chan_block_xfer_start(chan, desc);
}