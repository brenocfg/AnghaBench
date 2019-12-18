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
typedef  int u32 ;
struct enetc_hw {scalar_t__ reg; } ;
struct enetc_bdr {int index; scalar_t__ idr; scalar_t__ rcir; TYPE_1__* ndev; int /*<<< orphan*/  bd_count; int /*<<< orphan*/  bd_dma_base; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 scalar_t__ ENETC_BDR (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENETC_RBBAR0 ; 
 int /*<<< orphan*/  ENETC_RBBAR1 ; 
 int /*<<< orphan*/  ENETC_RBBSR ; 
 int /*<<< orphan*/  ENETC_RBCIR ; 
 int /*<<< orphan*/  ENETC_RBICIR0 ; 
 int ENETC_RBICIR0_ICEN ; 
 int /*<<< orphan*/  ENETC_RBLENR ; 
 int /*<<< orphan*/  ENETC_RBMR ; 
 int ENETC_RBMR_BDS ; 
 int ENETC_RBMR_EN ; 
 int ENETC_RBMR_VTE ; 
 int /*<<< orphan*/  ENETC_RBPIR ; 
 int ENETC_RTBLENR_LEN (int /*<<< orphan*/ ) ; 
 int ENETC_RXB_DMA_SIZE ; 
 scalar_t__ ENETC_SIRXIDR ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  RX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  enetc_bd_unused (struct enetc_bdr*) ; 
 int /*<<< orphan*/  enetc_refill_rx_ring (struct enetc_bdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_rxbdr_wr (struct enetc_hw*,int,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_setup_rxbdr(struct enetc_hw *hw, struct enetc_bdr *rx_ring)
{
	int idx = rx_ring->index;
	u32 rbmr;

	enetc_rxbdr_wr(hw, idx, ENETC_RBBAR0,
		       lower_32_bits(rx_ring->bd_dma_base));

	enetc_rxbdr_wr(hw, idx, ENETC_RBBAR1,
		       upper_32_bits(rx_ring->bd_dma_base));

	WARN_ON(!IS_ALIGNED(rx_ring->bd_count, 64)); /* multiple of 64 */
	enetc_rxbdr_wr(hw, idx, ENETC_RBLENR,
		       ENETC_RTBLENR_LEN(rx_ring->bd_count));

	enetc_rxbdr_wr(hw, idx, ENETC_RBBSR, ENETC_RXB_DMA_SIZE);

	enetc_rxbdr_wr(hw, idx, ENETC_RBPIR, 0);

	/* enable Rx ints by setting pkt thr to 1 */
	enetc_rxbdr_wr(hw, idx, ENETC_RBICIR0, ENETC_RBICIR0_ICEN | 0x1);

	rbmr = ENETC_RBMR_EN;
#ifdef CONFIG_FSL_ENETC_HW_TIMESTAMPING
	rbmr |= ENETC_RBMR_BDS;
#endif
	if (rx_ring->ndev->features & NETIF_F_HW_VLAN_CTAG_RX)
		rbmr |= ENETC_RBMR_VTE;

	rx_ring->rcir = hw->reg + ENETC_BDR(RX, idx, ENETC_RBCIR);
	rx_ring->idr = hw->reg + ENETC_SIRXIDR;

	enetc_refill_rx_ring(rx_ring, enetc_bd_unused(rx_ring));

	/* enable ring */
	enetc_rxbdr_wr(hw, idx, ENETC_RBMR, rbmr);
}