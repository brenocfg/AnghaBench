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
struct zynqmp_dma_desc_sw {int /*<<< orphan*/  dst_p; int /*<<< orphan*/  src_p; } ;
struct zynqmp_dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZYNQMP_DMA_DST_START_LSB ; 
 int /*<<< orphan*/  ZYNQMP_DMA_SRC_START_LSB ; 
 int /*<<< orphan*/  zynqmp_dma_writeq (struct zynqmp_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zynqmp_dma_update_desc_to_ctrlr(struct zynqmp_dma_chan *chan,
				      struct zynqmp_dma_desc_sw *desc)
{
	dma_addr_t addr;

	addr = desc->src_p;
	zynqmp_dma_writeq(chan, ZYNQMP_DMA_SRC_START_LSB, addr);
	addr = desc->dst_p;
	zynqmp_dma_writeq(chan, ZYNQMP_DMA_DST_START_LSB, addr);
}