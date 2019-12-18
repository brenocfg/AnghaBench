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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct i40e_netdev_priv {TYPE_2__* vsi; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct i40e_hw {TYPE_3__ mac; } ;
struct TYPE_5__ {TYPE_1__* back; } ;
struct TYPE_4__ {struct i40e_hw hw; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  I40E_GLPCI_LBARCTRL ; 
 int I40E_GLPCI_LBARCTRL_FL_SIZE_MASK ; 
 int I40E_GLPCI_LBARCTRL_FL_SIZE_SHIFT ; 
 scalar_t__ I40E_MAC_X722 ; 
 int X722_EEPROM_SCOPE_LIMIT ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_get_eeprom_len(struct net_device *netdev)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_hw *hw = &np->vsi->back->hw;
	u32 val;

#define X722_EEPROM_SCOPE_LIMIT 0x5B9FFF
	if (hw->mac.type == I40E_MAC_X722) {
		val = X722_EEPROM_SCOPE_LIMIT + 1;
		return val;
	}
	val = (rd32(hw, I40E_GLPCI_LBARCTRL)
		& I40E_GLPCI_LBARCTRL_FL_SIZE_MASK)
		>> I40E_GLPCI_LBARCTRL_FL_SIZE_SHIFT;
	/* register returns value in power of 2, 64Kbyte chunks. */
	val = (64 * 1024) * BIT(val);
	return val;
}