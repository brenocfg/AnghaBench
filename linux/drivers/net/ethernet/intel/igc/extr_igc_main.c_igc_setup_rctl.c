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
typedef  int u32 ;
struct TYPE_3__ {int mc_filter_type; } ;
struct igc_hw {TYPE_1__ mac; } ;
struct igc_adapter {TYPE_2__* netdev; struct igc_hw hw; } ;
struct TYPE_4__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_RCTL ; 
 int IGC_RCTL_BAM ; 
 int IGC_RCTL_CFIEN ; 
 int IGC_RCTL_DPF ; 
 int IGC_RCTL_EN ; 
 int IGC_RCTL_LBM_MAC ; 
 int IGC_RCTL_LBM_TCVR ; 
 int IGC_RCTL_LPE ; 
 int IGC_RCTL_MO_SHIFT ; 
 int IGC_RCTL_PMCF ; 
 int IGC_RCTL_RDMTS_HALF ; 
 int IGC_RCTL_SBP ; 
 int IGC_RCTL_SECRC ; 
 int IGC_RCTL_SZ_256 ; 
 int /*<<< orphan*/  IGC_RXDCTL (int /*<<< orphan*/ ) ; 
 int NETIF_F_RXALL ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void igc_setup_rctl(struct igc_adapter *adapter)
{
	struct igc_hw *hw = &adapter->hw;
	u32 rctl;

	rctl = rd32(IGC_RCTL);

	rctl &= ~(3 << IGC_RCTL_MO_SHIFT);
	rctl &= ~(IGC_RCTL_LBM_TCVR | IGC_RCTL_LBM_MAC);

	rctl |= IGC_RCTL_EN | IGC_RCTL_BAM | IGC_RCTL_RDMTS_HALF |
		(hw->mac.mc_filter_type << IGC_RCTL_MO_SHIFT);

	/* enable stripping of CRC. Newer features require
	 * that the HW strips the CRC.
	 */
	rctl |= IGC_RCTL_SECRC;

	/* disable store bad packets and clear size bits. */
	rctl &= ~(IGC_RCTL_SBP | IGC_RCTL_SZ_256);

	/* enable LPE to allow for reception of jumbo frames */
	rctl |= IGC_RCTL_LPE;

	/* disable queue 0 to prevent tail write w/o re-config */
	wr32(IGC_RXDCTL(0), 0);

	/* This is useful for sniffing bad packets. */
	if (adapter->netdev->features & NETIF_F_RXALL) {
		/* UPE and MPE will be handled by normal PROMISC logic
		 * in set_rx_mode
		 */
		rctl |= (IGC_RCTL_SBP | /* Receive bad packets */
			 IGC_RCTL_BAM | /* RX All Bcast Pkts */
			 IGC_RCTL_PMCF); /* RX All MAC Ctrl Pkts */

		rctl &= ~(IGC_RCTL_DPF | /* Allow filtered pause */
			  IGC_RCTL_CFIEN); /* Disable VLAN CFIEN Filter */
	}

	wr32(IGC_RCTL, rctl);
}