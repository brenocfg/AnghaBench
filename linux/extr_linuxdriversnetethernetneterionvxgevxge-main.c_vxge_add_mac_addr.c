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
struct vxgedev {struct vxge_vpath* vpaths; } ;
struct vxge_vpath {int /*<<< orphan*/  device_id; int /*<<< orphan*/  handle; } ;
struct macInfo {size_t vpath_no; int /*<<< orphan*/  macmask; int /*<<< orphan*/  macaddr; } ;
typedef  enum vxge_hw_vpath_mac_addr_add_mode { ____Placeholder_vxge_hw_vpath_mac_addr_add_mode } vxge_hw_vpath_mac_addr_add_mode ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  VXGE_ERR ; 
 int VXGE_HW_OK ; 
 int VXGE_HW_VPATH_MAC_ADDR_ADD_DUPLICATE ; 
 int VXGE_HW_VPATH_MAC_ADDR_REPLACE_DUPLICATE ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_debug_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int vxge_hw_vpath_mac_addr_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vxge_mac_list_add (struct vxge_vpath*,struct macInfo*) ; 

__attribute__((used)) static enum vxge_hw_status
vxge_add_mac_addr(struct vxgedev *vdev, struct macInfo *mac)
{
	enum vxge_hw_status status = VXGE_HW_OK;
	struct vxge_vpath *vpath;
	enum vxge_hw_vpath_mac_addr_add_mode duplicate_mode;

	if (is_multicast_ether_addr(mac->macaddr))
		duplicate_mode = VXGE_HW_VPATH_MAC_ADDR_ADD_DUPLICATE;
	else
		duplicate_mode = VXGE_HW_VPATH_MAC_ADDR_REPLACE_DUPLICATE;

	vpath = &vdev->vpaths[mac->vpath_no];
	status = vxge_hw_vpath_mac_addr_add(vpath->handle, mac->macaddr,
						mac->macmask, duplicate_mode);
	if (status != VXGE_HW_OK) {
		vxge_debug_init(VXGE_ERR,
			"DA config add entry failed for vpath:%d",
			vpath->device_id);
	} else
		if (FALSE == vxge_mac_list_add(vpath, mac))
			status = -EPERM;

	return status;
}