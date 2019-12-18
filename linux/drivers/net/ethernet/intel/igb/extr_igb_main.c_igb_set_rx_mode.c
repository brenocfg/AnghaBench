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
struct net_device {int flags; int features; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {unsigned int vfs_allocated_count; int max_frame_size; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_RCTL ; 
 int E1000_RCTL_MPE ; 
 int E1000_RCTL_UPE ; 
 int E1000_RCTL_VFE ; 
 int /*<<< orphan*/  E1000_RLPML ; 
 int /*<<< orphan*/  E1000_VMOLR (unsigned int) ; 
 int E1000_VMOLR_LPE ; 
 int E1000_VMOLR_MPME ; 
 int E1000_VMOLR_RLPML_MASK ; 
 int E1000_VMOLR_ROMPE ; 
 int E1000_VMOLR_ROPE ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int IGB_MAX_FRAME_BUILD_SKB ; 
 int MAX_JUMBO_FRAME_SIZE ; 
 int NETIF_F_RXALL ; 
 scalar_t__ __dev_uc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_82576 ; 
 scalar_t__ e1000_i350 ; 
 int /*<<< orphan*/  igb_restore_vf_multicasts (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_set_uta (struct igb_adapter*,int) ; 
 int /*<<< orphan*/  igb_uc_sync ; 
 int /*<<< orphan*/  igb_uc_unsync ; 
 int /*<<< orphan*/  igb_vlan_promisc_disable (struct igb_adapter*) ; 
 scalar_t__ igb_vlan_promisc_enable (struct igb_adapter*) ; 
 int igb_write_mc_addr_list (struct net_device*) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void igb_set_rx_mode(struct net_device *netdev)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	unsigned int vfn = adapter->vfs_allocated_count;
	u32 rctl = 0, vmolr = 0, rlpml = MAX_JUMBO_FRAME_SIZE;
	int count;

	/* Check for Promiscuous and All Multicast modes */
	if (netdev->flags & IFF_PROMISC) {
		rctl |= E1000_RCTL_UPE | E1000_RCTL_MPE;
		vmolr |= E1000_VMOLR_MPME;

		/* enable use of UTA filter to force packets to default pool */
		if (hw->mac.type == e1000_82576)
			vmolr |= E1000_VMOLR_ROPE;
	} else {
		if (netdev->flags & IFF_ALLMULTI) {
			rctl |= E1000_RCTL_MPE;
			vmolr |= E1000_VMOLR_MPME;
		} else {
			/* Write addresses to the MTA, if the attempt fails
			 * then we should just turn on promiscuous mode so
			 * that we can at least receive multicast traffic
			 */
			count = igb_write_mc_addr_list(netdev);
			if (count < 0) {
				rctl |= E1000_RCTL_MPE;
				vmolr |= E1000_VMOLR_MPME;
			} else if (count) {
				vmolr |= E1000_VMOLR_ROMPE;
			}
		}
	}

	/* Write addresses to available RAR registers, if there is not
	 * sufficient space to store all the addresses then enable
	 * unicast promiscuous mode
	 */
	if (__dev_uc_sync(netdev, igb_uc_sync, igb_uc_unsync)) {
		rctl |= E1000_RCTL_UPE;
		vmolr |= E1000_VMOLR_ROPE;
	}

	/* enable VLAN filtering by default */
	rctl |= E1000_RCTL_VFE;

	/* disable VLAN filtering for modes that require it */
	if ((netdev->flags & IFF_PROMISC) ||
	    (netdev->features & NETIF_F_RXALL)) {
		/* if we fail to set all rules then just clear VFE */
		if (igb_vlan_promisc_enable(adapter))
			rctl &= ~E1000_RCTL_VFE;
	} else {
		igb_vlan_promisc_disable(adapter);
	}

	/* update state of unicast, multicast, and VLAN filtering modes */
	rctl |= rd32(E1000_RCTL) & ~(E1000_RCTL_UPE | E1000_RCTL_MPE |
				     E1000_RCTL_VFE);
	wr32(E1000_RCTL, rctl);

#if (PAGE_SIZE < 8192)
	if (!adapter->vfs_allocated_count) {
		if (adapter->max_frame_size <= IGB_MAX_FRAME_BUILD_SKB)
			rlpml = IGB_MAX_FRAME_BUILD_SKB;
	}
#endif
	wr32(E1000_RLPML, rlpml);

	/* In order to support SR-IOV and eventually VMDq it is necessary to set
	 * the VMOLR to enable the appropriate modes.  Without this workaround
	 * we will have issues with VLAN tag stripping not being done for frames
	 * that are only arriving because we are the default pool
	 */
	if ((hw->mac.type < e1000_82576) || (hw->mac.type > e1000_i350))
		return;

	/* set UTA to appropriate mode */
	igb_set_uta(adapter, !!(vmolr & E1000_VMOLR_ROPE));

	vmolr |= rd32(E1000_VMOLR(vfn)) &
		 ~(E1000_VMOLR_ROPE | E1000_VMOLR_MPME | E1000_VMOLR_ROMPE);

	/* enable Rx jumbo frames, restrict as needed to support build_skb */
	vmolr &= ~E1000_VMOLR_RLPML_MASK;
#if (PAGE_SIZE < 8192)
	if (adapter->max_frame_size <= IGB_MAX_FRAME_BUILD_SKB)
		vmolr |= IGB_MAX_FRAME_BUILD_SKB;
	else
#endif
		vmolr |= MAX_JUMBO_FRAME_SIZE;
	vmolr |= E1000_VMOLR_LPE;

	wr32(E1000_VMOLR(vfn), vmolr);

	igb_restore_vf_multicasts(adapter);
}