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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_source_address_pruning ) (struct ixgbe_hw*,int,unsigned int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct ixgbe_adapter {unsigned int num_vfs; unsigned int num_rx_pools; int bridge_mode; struct ixgbe_hw hw; } ;
typedef  int __u16 ;

/* Variables and functions */
#define  BRIDGE_MODE_VEB 129 
#define  BRIDGE_MODE_VEPA 128 
 int EINVAL ; 
 int /*<<< orphan*/  IXGBE_PFDTXGSWC ; 
 int /*<<< orphan*/  IXGBE_PFDTXGSWC_VT_LBEN ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VMD_CTL ; 
 int /*<<< orphan*/  IXGBE_VT_CTL_REPLEN ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_info (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int,unsigned int) ; 

__attribute__((used)) static int ixgbe_configure_bridge_mode(struct ixgbe_adapter *adapter,
				       __u16 mode)
{
	struct ixgbe_hw *hw = &adapter->hw;
	unsigned int p, num_pools;
	u32 vmdctl;

	switch (mode) {
	case BRIDGE_MODE_VEPA:
		/* disable Tx loopback, rely on switch hairpin mode */
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_PFDTXGSWC, 0);

		/* must enable Rx switching replication to allow multicast
		 * packet reception on all VFs, and to enable source address
		 * pruning.
		 */
		vmdctl = IXGBE_READ_REG(hw, IXGBE_VMD_CTL);
		vmdctl |= IXGBE_VT_CTL_REPLEN;
		IXGBE_WRITE_REG(hw, IXGBE_VMD_CTL, vmdctl);

		/* enable Rx source address pruning. Note, this requires
		 * replication to be enabled or else it does nothing.
		 */
		num_pools = adapter->num_vfs + adapter->num_rx_pools;
		for (p = 0; p < num_pools; p++) {
			if (hw->mac.ops.set_source_address_pruning)
				hw->mac.ops.set_source_address_pruning(hw,
								       true,
								       p);
		}
		break;
	case BRIDGE_MODE_VEB:
		/* enable Tx loopback for internal VF/PF communication */
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_PFDTXGSWC,
				IXGBE_PFDTXGSWC_VT_LBEN);

		/* disable Rx switching replication unless we have SR-IOV
		 * virtual functions
		 */
		vmdctl = IXGBE_READ_REG(hw, IXGBE_VMD_CTL);
		if (!adapter->num_vfs)
			vmdctl &= ~IXGBE_VT_CTL_REPLEN;
		IXGBE_WRITE_REG(hw, IXGBE_VMD_CTL, vmdctl);

		/* disable Rx source address pruning, since we don't expect to
		 * be receiving external loopback of our transmitted frames.
		 */
		num_pools = adapter->num_vfs + adapter->num_rx_pools;
		for (p = 0; p < num_pools; p++) {
			if (hw->mac.ops.set_source_address_pruning)
				hw->mac.ops.set_source_address_pruning(hw,
								       false,
								       p);
		}
		break;
	default:
		return -EINVAL;
	}

	adapter->bridge_mode = mode;

	e_info(drv, "enabling bridge mode: %s\n",
	       mode == BRIDGE_MODE_VEPA ? "VEPA" : "VEB");

	return 0;
}