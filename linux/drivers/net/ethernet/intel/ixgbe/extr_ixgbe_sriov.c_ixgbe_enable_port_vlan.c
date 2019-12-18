#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {TYPE_3__* pdev; int /*<<< orphan*/  state; TYPE_2__* vfinfo; struct ixgbe_hw hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  pf_qos; int /*<<< orphan*/  pf_vlan; } ;

/* Variables and functions */
 int IXGBE_QDE_ENABLE ; 
 int IXGBE_QDE_HIDE_VLAN ; 
 int /*<<< orphan*/  __IXGBE_DOWN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ixgbe_mac_X550 ; 
 int ixgbe_set_vf_vlan (struct ixgbe_adapter*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgbe_set_vmolr (struct ixgbe_hw*,int,int) ; 
 int /*<<< orphan*/  ixgbe_set_vmvir (struct ixgbe_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgbe_write_qde (struct ixgbe_adapter*,int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ixgbe_enable_port_vlan(struct ixgbe_adapter *adapter, int vf,
				  u16 vlan, u8 qos)
{
	struct ixgbe_hw *hw = &adapter->hw;
	int err;

	err = ixgbe_set_vf_vlan(adapter, true, vlan, vf);
	if (err)
		goto out;

	/* Revoke tagless access via VLAN 0 */
	ixgbe_set_vf_vlan(adapter, false, 0, vf);

	ixgbe_set_vmvir(adapter, vlan, qos, vf);
	ixgbe_set_vmolr(hw, vf, false);

	/* enable hide vlan on X550 */
	if (hw->mac.type >= ixgbe_mac_X550)
		ixgbe_write_qde(adapter, vf, IXGBE_QDE_ENABLE |
				IXGBE_QDE_HIDE_VLAN);

	adapter->vfinfo[vf].pf_vlan = vlan;
	adapter->vfinfo[vf].pf_qos = qos;
	dev_info(&adapter->pdev->dev,
		 "Setting VLAN %d, QOS 0x%x on VF %d\n", vlan, qos, vf);
	if (test_bit(__IXGBE_DOWN, &adapter->state)) {
		dev_warn(&adapter->pdev->dev,
			 "The VF VLAN has been set, but the PF device is not up.\n");
		dev_warn(&adapter->pdev->dev,
			 "Bring the PF device up before attempting to use the VF device.\n");
	}

out:
	return err;
}