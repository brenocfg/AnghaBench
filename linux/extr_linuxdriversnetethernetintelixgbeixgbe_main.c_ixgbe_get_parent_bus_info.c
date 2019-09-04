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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  width; int /*<<< orphan*/  type; } ;
struct ixgbe_hw {TYPE_1__ bus; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_bus_type_pci_express ; 
 int /*<<< orphan*/  ixgbe_convert_bus_speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_convert_bus_width (int /*<<< orphan*/ ) ; 
 int ixgbe_read_pci_cfg_word_parent (struct ixgbe_adapter*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 ixgbe_get_parent_bus_info(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u16 link_status = 0;
	int err;

	hw->bus.type = ixgbe_bus_type_pci_express;

	/* Get the negotiated link width and speed from PCI config space of the
	 * parent, as this device is behind a switch
	 */
	err = ixgbe_read_pci_cfg_word_parent(adapter, 18, &link_status);

	/* assume caller will handle error case */
	if (err)
		return err;

	hw->bus.width = ixgbe_convert_bus_width(link_status);
	hw->bus.speed = ixgbe_convert_bus_speed(link_status);

	return 0;
}