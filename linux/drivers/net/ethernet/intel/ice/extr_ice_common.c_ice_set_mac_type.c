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
struct ice_hw {scalar_t__ vendor_id; int /*<<< orphan*/  mac_type; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_DEVICE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ICE_MAC_GENERIC ; 
 scalar_t__ PCI_VENDOR_ID_INTEL ; 

__attribute__((used)) static enum ice_status ice_set_mac_type(struct ice_hw *hw)
{
	if (hw->vendor_id != PCI_VENDOR_ID_INTEL)
		return ICE_ERR_DEVICE_NOT_SUPPORTED;

	hw->mac_type = ICE_MAC_GENERIC;
	return 0;
}