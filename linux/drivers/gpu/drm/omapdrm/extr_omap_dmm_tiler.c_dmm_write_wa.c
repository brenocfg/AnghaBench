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
struct dmm {scalar_t__ base; int /*<<< orphan*/  dev; scalar_t__ phys_base; scalar_t__ wa_dma_handle; scalar_t__ wa_dma_data; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dmm_dma_copy (struct dmm*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void dmm_write_wa(struct dmm *dmm, u32 val, u32 reg)
{
	dma_addr_t src, dst;
	int r;

	writel(val, dmm->wa_dma_data);
	/*
	 * As per i878 workaround, the DMA is used to access the DMM registers.
	 * Make sure that the writel is not moved by the compiler or the CPU, so
	 * the data will be in place before we start the DMA to do the actual
	 * register write.
	 */
	wmb();

	src = dmm->wa_dma_handle;
	dst = dmm->phys_base + reg;

	r = dmm_dma_copy(dmm, src, dst);
	if (r) {
		dev_err(dmm->dev, "sDMA write transfer timeout\n");
		writel(val, dmm->base + reg);
	}
}