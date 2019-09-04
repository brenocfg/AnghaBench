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
struct idma64 {int /*<<< orphan*/  all_chan_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK ; 
 int /*<<< orphan*/  CFG ; 
 int /*<<< orphan*/  DST_TRAN ; 
 int /*<<< orphan*/  ERROR ; 
 int IDMA64_CFG_DMA_EN ; 
 int /*<<< orphan*/  MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRC_TRAN ; 
 int /*<<< orphan*/  XFER ; 
 int /*<<< orphan*/  channel_clear_bit (struct idma64*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int dma_readl (struct idma64*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_writel (struct idma64*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idma64_off(struct idma64 *idma64)
{
	unsigned short count = 100;

	dma_writel(idma64, CFG, 0);

	channel_clear_bit(idma64, MASK(XFER), idma64->all_chan_mask);
	channel_clear_bit(idma64, MASK(BLOCK), idma64->all_chan_mask);
	channel_clear_bit(idma64, MASK(SRC_TRAN), idma64->all_chan_mask);
	channel_clear_bit(idma64, MASK(DST_TRAN), idma64->all_chan_mask);
	channel_clear_bit(idma64, MASK(ERROR), idma64->all_chan_mask);

	do {
		cpu_relax();
	} while (dma_readl(idma64, CFG) & IDMA64_CFG_DMA_EN && --count);
}