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
typedef  int u16 ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_VMVIR (int) ; 
 int IXGBE_VMVIR_VLANA_DEFAULT ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int VLAN_PRIO_SHIFT ; 

__attribute__((used)) static inline void ixgbe_set_vmvir(struct ixgbe_adapter *adapter,
				   u16 vid, u16 qos, u32 vf)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 vmvir = vid | (qos << VLAN_PRIO_SHIFT) | IXGBE_VMVIR_VLANA_DEFAULT;

	IXGBE_WRITE_REG(hw, IXGBE_VMVIR(vf), vmvir);
}