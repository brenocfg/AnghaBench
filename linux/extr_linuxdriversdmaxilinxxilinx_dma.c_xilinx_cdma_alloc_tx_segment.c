#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xilinx_dma_chan {int /*<<< orphan*/  desc_pool; } ;
struct xilinx_cdma_tx_segment {int /*<<< orphan*/  phys; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct xilinx_cdma_tx_segment* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct xilinx_cdma_tx_segment *
xilinx_cdma_alloc_tx_segment(struct xilinx_dma_chan *chan)
{
	struct xilinx_cdma_tx_segment *segment;
	dma_addr_t phys;

	segment = dma_pool_zalloc(chan->desc_pool, GFP_ATOMIC, &phys);
	if (!segment)
		return NULL;

	segment->phys = phys;

	return segment;
}