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
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {TYPE_2__* netdev; scalar_t__ vfs_allocated_count; struct e1000_hw hw; } ;
struct TYPE_4__ {int features; } ;

/* Variables and functions */
 int ALL_QUEUES ; 
 int /*<<< orphan*/  E1000_QDE ; 
 int /*<<< orphan*/  E1000_RCTL ; 
 int E1000_RCTL_BAM ; 
 int E1000_RCTL_CFIEN ; 
 int E1000_RCTL_DPF ; 
 int E1000_RCTL_EN ; 
 int E1000_RCTL_LBM_MAC ; 
 int E1000_RCTL_LBM_TCVR ; 
 int E1000_RCTL_LPE ; 
 int E1000_RCTL_MO_SHIFT ; 
 int E1000_RCTL_PMCF ; 
 int E1000_RCTL_RDMTS_HALF ; 
 int E1000_RCTL_SBP ; 
 int E1000_RCTL_SECRC ; 
 int E1000_RCTL_SZ_256 ; 
 int /*<<< orphan*/  E1000_RXDCTL (int /*<<< orphan*/ ) ; 
 int NETIF_F_RXALL ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

void igb_setup_rctl(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 rctl;

	rctl = rd32(E1000_RCTL);

	rctl &= ~(3 << E1000_RCTL_MO_SHIFT);
	rctl &= ~(E1000_RCTL_LBM_TCVR | E1000_RCTL_LBM_MAC);

	rctl |= E1000_RCTL_EN | E1000_RCTL_BAM | E1000_RCTL_RDMTS_HALF |
		(hw->mac.mc_filter_type << E1000_RCTL_MO_SHIFT);

	/* enable stripping of CRC. It's unlikely this will break BMC
	 * redirection as it did with e1000. Newer features require
	 * that the HW strips the CRC.
	 */
	rctl |= E1000_RCTL_SECRC;

	/* disable store bad packets and clear size bits. */
	rctl &= ~(E1000_RCTL_SBP | E1000_RCTL_SZ_256);

	/* enable LPE to allow for reception of jumbo frames */
	rctl |= E1000_RCTL_LPE;

	/* disable queue 0 to prevent tail write w/o re-config */
	wr32(E1000_RXDCTL(0), 0);

	/* Attention!!!  For SR-IOV PF driver operations you must enable
	 * queue drop for all VF and PF queues to prevent head of line blocking
	 * if an un-trusted VF does not provide descriptors to hardware.
	 */
	if (adapter->vfs_allocated_count) {
		/* set all queue drop enable bits */
		wr32(E1000_QDE, ALL_QUEUES);
	}

	/* This is useful for sniffing bad packets. */
	if (adapter->netdev->features & NETIF_F_RXALL) {
		/* UPE and MPE will be handled by normal PROMISC logic
		 * in e1000e_set_rx_mode
		 */
		rctl |= (E1000_RCTL_SBP | /* Receive bad packets */
			 E1000_RCTL_BAM | /* RX All Bcast Pkts */
			 E1000_RCTL_PMCF); /* RX All MAC Ctrl Pkts */

		rctl &= ~(E1000_RCTL_DPF | /* Allow filtered pause */
			  E1000_RCTL_CFIEN); /* Dis VLAN CFIEN Filter */
		/* Do not mess with E1000_CTRL_VME, it affects transmit as well,
		 * and that breaks VLANs.
		 */
	}

	wr32(E1000_RCTL, rctl);
}