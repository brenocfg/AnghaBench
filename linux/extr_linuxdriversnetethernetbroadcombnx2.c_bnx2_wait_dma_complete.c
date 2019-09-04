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
typedef  int u32 ;
struct bnx2 {int dummy; } ;

/* Variables and functions */
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5706 ; 
 scalar_t__ BNX2_CHIP_5708 ; 
 int /*<<< orphan*/  BNX2_MISC_ENABLE_CLR_BITS ; 
 int BNX2_MISC_ENABLE_CLR_BITS_DMA_ENGINE_ENABLE ; 
 int BNX2_MISC_ENABLE_CLR_BITS_HOST_COALESCE_ENABLE ; 
 int BNX2_MISC_ENABLE_CLR_BITS_RX_DMA_ENABLE ; 
 int BNX2_MISC_ENABLE_CLR_BITS_TX_DMA_ENABLE ; 
 int /*<<< orphan*/  BNX2_MISC_NEW_CORE_CTL ; 
 int BNX2_MISC_NEW_CORE_CTL_DMA_ENABLE ; 
 int /*<<< orphan*/  BNX2_PCICFG_DEVICE_CONTROL ; 
 int BNX2_PCICFG_DEVICE_STATUS_NO_PEND ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
bnx2_wait_dma_complete(struct bnx2 *bp)
{
	u32 val;
	int i;

	/*
	 * Wait for the current PCI transaction to complete before
	 * issuing a reset.
	 */
	if ((BNX2_CHIP(bp) == BNX2_CHIP_5706) ||
	    (BNX2_CHIP(bp) == BNX2_CHIP_5708)) {
		BNX2_WR(bp, BNX2_MISC_ENABLE_CLR_BITS,
			BNX2_MISC_ENABLE_CLR_BITS_TX_DMA_ENABLE |
			BNX2_MISC_ENABLE_CLR_BITS_DMA_ENGINE_ENABLE |
			BNX2_MISC_ENABLE_CLR_BITS_RX_DMA_ENABLE |
			BNX2_MISC_ENABLE_CLR_BITS_HOST_COALESCE_ENABLE);
		val = BNX2_RD(bp, BNX2_MISC_ENABLE_CLR_BITS);
		udelay(5);
	} else {  /* 5709 */
		val = BNX2_RD(bp, BNX2_MISC_NEW_CORE_CTL);
		val &= ~BNX2_MISC_NEW_CORE_CTL_DMA_ENABLE;
		BNX2_WR(bp, BNX2_MISC_NEW_CORE_CTL, val);
		val = BNX2_RD(bp, BNX2_MISC_NEW_CORE_CTL);

		for (i = 0; i < 100; i++) {
			msleep(1);
			val = BNX2_RD(bp, BNX2_PCICFG_DEVICE_CONTROL);
			if (!(val & BNX2_PCICFG_DEVICE_STATUS_NO_PEND))
				break;
		}
	}

	return;
}