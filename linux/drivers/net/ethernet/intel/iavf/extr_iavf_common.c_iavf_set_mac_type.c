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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct iavf_hw {scalar_t__ vendor_id; int device_id; TYPE_1__ mac; } ;
typedef  enum iavf_status { ____Placeholder_iavf_status } iavf_status ;

/* Variables and functions */
#define  IAVF_DEV_ID_ADAPTIVE_VF 131 
#define  IAVF_DEV_ID_VF 130 
#define  IAVF_DEV_ID_VF_HV 129 
#define  IAVF_DEV_ID_X722_VF 128 
 int IAVF_ERR_DEVICE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  IAVF_MAC_GENERIC ; 
 int /*<<< orphan*/  IAVF_MAC_VF ; 
 int /*<<< orphan*/  IAVF_MAC_X722_VF ; 
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  hw_dbg (struct iavf_hw*,char*,int /*<<< orphan*/ ,int) ; 

enum iavf_status iavf_set_mac_type(struct iavf_hw *hw)
{
	enum iavf_status status = 0;

	if (hw->vendor_id == PCI_VENDOR_ID_INTEL) {
		switch (hw->device_id) {
		case IAVF_DEV_ID_X722_VF:
			hw->mac.type = IAVF_MAC_X722_VF;
			break;
		case IAVF_DEV_ID_VF:
		case IAVF_DEV_ID_VF_HV:
		case IAVF_DEV_ID_ADAPTIVE_VF:
			hw->mac.type = IAVF_MAC_VF;
			break;
		default:
			hw->mac.type = IAVF_MAC_GENERIC;
			break;
		}
	} else {
		status = IAVF_ERR_DEVICE_NOT_SUPPORTED;
	}

	hw_dbg(hw, "found mac: %d, returns: %d\n", hw->mac.type, status);
	return status;
}