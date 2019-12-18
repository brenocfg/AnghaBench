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
struct cp_private {int ring_dma; int /*<<< orphan*/  dev; int /*<<< orphan*/  cpcmd; } ;
struct cp_desc {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int CP_RX_RING_SIZE ; 
 int /*<<< orphan*/  Cmd ; 
 int /*<<< orphan*/  CpCmd ; 
 scalar_t__ HiTxRingAddr ; 
 int RxOn ; 
 scalar_t__ RxRingAddr ; 
 int TxOn ; 
 scalar_t__ TxRingAddr ; 
 int /*<<< orphan*/  cpw16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpw32_f (scalar_t__,int) ; 
 int /*<<< orphan*/  cpw8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_reset_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cp_start_hw (struct cp_private *cp)
{
	dma_addr_t ring_dma;

	cpw16(CpCmd, cp->cpcmd);

	/*
	 * These (at least TxRingAddr) need to be configured after the
	 * corresponding bits in CpCmd are enabled. Datasheet v1.6 §6.33
	 * (C+ Command Register) recommends that these and more be configured
	 * *after* the [RT]xEnable bits in CpCmd are set. And on some hardware
	 * it's been observed that the TxRingAddr is actually reset to garbage
	 * when C+ mode Tx is enabled in CpCmd.
	 */
	cpw32_f(HiTxRingAddr, 0);
	cpw32_f(HiTxRingAddr + 4, 0);

	ring_dma = cp->ring_dma;
	cpw32_f(RxRingAddr, ring_dma & 0xffffffff);
	cpw32_f(RxRingAddr + 4, (ring_dma >> 16) >> 16);

	ring_dma += sizeof(struct cp_desc) * CP_RX_RING_SIZE;
	cpw32_f(TxRingAddr, ring_dma & 0xffffffff);
	cpw32_f(TxRingAddr + 4, (ring_dma >> 16) >> 16);

	/*
	 * Strictly speaking, the datasheet says this should be enabled
	 * *before* setting the descriptor addresses. But what, then, would
	 * prevent it from doing DMA to random unconfigured addresses?
	 * This variant appears to work fine.
	 */
	cpw8(Cmd, RxOn | TxOn);

	netdev_reset_queue(cp->dev);
}