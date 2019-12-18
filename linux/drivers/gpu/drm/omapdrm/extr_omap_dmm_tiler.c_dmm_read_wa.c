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
typedef  scalar_t__ u32 ;
struct dmm {scalar_t__ wa_dma_data; scalar_t__ base; int /*<<< orphan*/  dev; scalar_t__ wa_dma_handle; scalar_t__ phys_base; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dmm_dma_copy (struct dmm*,scalar_t__,scalar_t__) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static u32 dmm_read_wa(struct dmm *dmm, u32 reg)
{
	dma_addr_t src, dst;
	int r;

	src = dmm->phys_base + reg;
	dst = dmm->wa_dma_handle;

	r = dmm_dma_copy(dmm, src, dst);
	if (r) {
		dev_err(dmm->dev, "sDMA read transfer timeout\n");
		return readl(dmm->base + reg);
	}

	/*
	 * As per i878 workaround, the DMA is used to access the DMM registers.
	 * Make sure that the readl is not moved by the compiler or the CPU
	 * earlier than the DMA finished writing the value to memory.
	 */
	rmb();
	return readl(dmm->wa_dma_data);
}