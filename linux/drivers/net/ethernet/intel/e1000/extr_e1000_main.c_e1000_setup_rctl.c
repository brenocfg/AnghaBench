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
struct e1000_hw {int mc_filter_type; int tbi_compatibility_on; } ;
struct e1000_adapter {int rx_buffer_len; TYPE_1__* netdev; struct e1000_hw hw; } ;
struct TYPE_2__ {scalar_t__ mtu; int features; } ;

/* Variables and functions */
 int E1000_RCTL_BAM ; 
 int E1000_RCTL_BSEX ; 
 int E1000_RCTL_CFIEN ; 
 int E1000_RCTL_DPF ; 
 int E1000_RCTL_LBM_NO ; 
 int E1000_RCTL_LPE ; 
 int E1000_RCTL_MO_SHIFT ; 
 int E1000_RCTL_PMCF ; 
 int E1000_RCTL_RDMTS_HALF ; 
 int E1000_RCTL_SBP ; 
 int E1000_RCTL_SZ_16384 ; 
 int E1000_RCTL_SZ_2048 ; 
 int E1000_RCTL_SZ_4096 ; 
 int E1000_RCTL_SZ_8192 ; 
 int E1000_RCTL_VFE ; 
#define  E1000_RXBUFFER_16384 131 
#define  E1000_RXBUFFER_2048 130 
#define  E1000_RXBUFFER_4096 129 
#define  E1000_RXBUFFER_8192 128 
 scalar_t__ ETH_DATA_LEN ; 
 int NETIF_F_RXALL ; 
 int /*<<< orphan*/  RCTL ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void e1000_setup_rctl(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 rctl;

	rctl = er32(RCTL);

	rctl &= ~(3 << E1000_RCTL_MO_SHIFT);

	rctl |= E1000_RCTL_BAM | E1000_RCTL_LBM_NO |
		E1000_RCTL_RDMTS_HALF |
		(hw->mc_filter_type << E1000_RCTL_MO_SHIFT);

	if (hw->tbi_compatibility_on == 1)
		rctl |= E1000_RCTL_SBP;
	else
		rctl &= ~E1000_RCTL_SBP;

	if (adapter->netdev->mtu <= ETH_DATA_LEN)
		rctl &= ~E1000_RCTL_LPE;
	else
		rctl |= E1000_RCTL_LPE;

	/* Setup buffer sizes */
	rctl &= ~E1000_RCTL_SZ_4096;
	rctl |= E1000_RCTL_BSEX;
	switch (adapter->rx_buffer_len) {
	case E1000_RXBUFFER_2048:
	default:
		rctl |= E1000_RCTL_SZ_2048;
		rctl &= ~E1000_RCTL_BSEX;
		break;
	case E1000_RXBUFFER_4096:
		rctl |= E1000_RCTL_SZ_4096;
		break;
	case E1000_RXBUFFER_8192:
		rctl |= E1000_RCTL_SZ_8192;
		break;
	case E1000_RXBUFFER_16384:
		rctl |= E1000_RCTL_SZ_16384;
		break;
	}

	/* This is useful for sniffing bad packets. */
	if (adapter->netdev->features & NETIF_F_RXALL) {
		/* UPE and MPE will be handled by normal PROMISC logic
		 * in e1000e_set_rx_mode
		 */
		rctl |= (E1000_RCTL_SBP | /* Receive bad packets */
			 E1000_RCTL_BAM | /* RX All Bcast Pkts */
			 E1000_RCTL_PMCF); /* RX All MAC Ctrl Pkts */

		rctl &= ~(E1000_RCTL_VFE | /* Disable VLAN filter */
			  E1000_RCTL_DPF | /* Allow filtered pause */
			  E1000_RCTL_CFIEN); /* Dis VLAN CFIEN Filter */
		/* Do not mess with E1000_CTRL_VME, it affects transmit as well,
		 * and that breaks VLANs.
		 */
	}

	ew32(RCTL, rctl);
}