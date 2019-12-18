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
struct TYPE_3__ {int /*<<< orphan*/  (* enable_rx_buff ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* disable_rx_buff ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {int type; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct ixgbe_adapter {int flags; int /*<<< orphan*/  fdir_pballoc; struct ixgbe_hw hw; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int IXGBE_FLAG_DCA_CAPABLE ; 
 int IXGBE_FLAG_FDIR_HASH_CAPABLE ; 
 int IXGBE_FLAG_FDIR_PERFECT_CAPABLE ; 
 int /*<<< orphan*/  ixgbe_configure_dcb (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_configure_dfwd (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_configure_fcoe (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_configure_pb (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_configure_rx (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_configure_tx (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_configure_virtualization (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_fdir_filter_restore (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_init_fdir_perfect_82599 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_init_fdir_signature_82599 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_ipsec_restore (struct ixgbe_adapter*) ; 
#define  ixgbe_mac_82599EB 129 
#define  ixgbe_mac_X540 128 
 int /*<<< orphan*/  ixgbe_restore_vlan (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_set_rx_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_setup_dca (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*) ; 

__attribute__((used)) static void ixgbe_configure(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;

	ixgbe_configure_pb(adapter);
#ifdef CONFIG_IXGBE_DCB
	ixgbe_configure_dcb(adapter);
#endif
	/*
	 * We must restore virtualization before VLANs or else
	 * the VLVF registers will not be populated
	 */
	ixgbe_configure_virtualization(adapter);

	ixgbe_set_rx_mode(adapter->netdev);
	ixgbe_restore_vlan(adapter);
	ixgbe_ipsec_restore(adapter);

	switch (hw->mac.type) {
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
		hw->mac.ops.disable_rx_buff(hw);
		break;
	default:
		break;
	}

	if (adapter->flags & IXGBE_FLAG_FDIR_HASH_CAPABLE) {
		ixgbe_init_fdir_signature_82599(&adapter->hw,
						adapter->fdir_pballoc);
	} else if (adapter->flags & IXGBE_FLAG_FDIR_PERFECT_CAPABLE) {
		ixgbe_init_fdir_perfect_82599(&adapter->hw,
					      adapter->fdir_pballoc);
		ixgbe_fdir_filter_restore(adapter);
	}

	switch (hw->mac.type) {
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
		hw->mac.ops.enable_rx_buff(hw);
		break;
	default:
		break;
	}

#ifdef CONFIG_IXGBE_DCA
	/* configure DCA */
	if (adapter->flags & IXGBE_FLAG_DCA_CAPABLE)
		ixgbe_setup_dca(adapter);
#endif /* CONFIG_IXGBE_DCA */

#ifdef IXGBE_FCOE
	/* configure FCoE L2 filters, redirection table, and Rx control */
	ixgbe_configure_fcoe(adapter);

#endif /* IXGBE_FCOE */
	ixgbe_configure_tx(adapter);
	ixgbe_configure_rx(adapter);
	ixgbe_configure_dfwd(adapter);
}