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
struct TYPE_3__ {scalar_t__ dstride; scalar_t__ sstride; } ;
struct st_fdma_hw_node {TYPE_1__ generic; int /*<<< orphan*/  saddr; int /*<<< orphan*/  control; int /*<<< orphan*/  daddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;
struct st_fdma_chan {TYPE_2__ cfg; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;

/* Variables and functions */
 int DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  FDMA_NODE_CTRL_DST_INCR ; 
 int /*<<< orphan*/  FDMA_NODE_CTRL_DST_STATIC ; 
 int /*<<< orphan*/  FDMA_NODE_CTRL_SRC_INCR ; 
 int /*<<< orphan*/  FDMA_NODE_CTRL_SRC_STATIC ; 

__attribute__((used)) static void fill_hw_node(struct st_fdma_hw_node *hw_node,
			struct st_fdma_chan *fchan,
			enum dma_transfer_direction direction)
{
	if (direction == DMA_MEM_TO_DEV) {
		hw_node->control |= FDMA_NODE_CTRL_SRC_INCR;
		hw_node->control |= FDMA_NODE_CTRL_DST_STATIC;
		hw_node->daddr = fchan->cfg.dev_addr;
	} else {
		hw_node->control |= FDMA_NODE_CTRL_SRC_STATIC;
		hw_node->control |= FDMA_NODE_CTRL_DST_INCR;
		hw_node->saddr = fchan->cfg.dev_addr;
	}

	hw_node->generic.sstride = 0;
	hw_node->generic.dstride = 0;
}