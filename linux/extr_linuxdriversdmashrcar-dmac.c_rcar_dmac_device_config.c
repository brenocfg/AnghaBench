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
struct TYPE_4__ {int /*<<< orphan*/  xfer_size; int /*<<< orphan*/  slave_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  xfer_size; int /*<<< orphan*/  slave_addr; } ;
struct rcar_dmac_chan {TYPE_2__ dst; TYPE_1__ src; } ;
struct dma_slave_config {int /*<<< orphan*/  dst_addr_width; int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct rcar_dmac_chan* to_rcar_dmac_chan (struct dma_chan*) ; 

__attribute__((used)) static int rcar_dmac_device_config(struct dma_chan *chan,
				   struct dma_slave_config *cfg)
{
	struct rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);

	/*
	 * We could lock this, but you shouldn't be configuring the
	 * channel, while using it...
	 */
	rchan->src.slave_addr = cfg->src_addr;
	rchan->dst.slave_addr = cfg->dst_addr;
	rchan->src.xfer_size = cfg->src_addr_width;
	rchan->dst.xfer_size = cfg->dst_addr_width;

	return 0;
}