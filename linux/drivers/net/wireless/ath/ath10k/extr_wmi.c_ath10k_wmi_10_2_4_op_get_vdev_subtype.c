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
struct ath10k {int dummy; } ;
typedef  enum wmi_vdev_subtype { ____Placeholder_wmi_vdev_subtype } wmi_vdev_subtype ;

/* Variables and functions */
 int ENOTSUPP ; 
 int WMI_VDEV_SUBTYPE_10_2_4_MESH_11S ; 
 int WMI_VDEV_SUBTYPE_10_2_4_NONE ; 
 int WMI_VDEV_SUBTYPE_10_2_4_P2P_CLI ; 
 int WMI_VDEV_SUBTYPE_10_2_4_P2P_DEV ; 
 int WMI_VDEV_SUBTYPE_10_2_4_P2P_GO ; 
 int WMI_VDEV_SUBTYPE_10_2_4_PROXY_STA ; 
#define  WMI_VDEV_SUBTYPE_MESH_11S 134 
#define  WMI_VDEV_SUBTYPE_MESH_NON_11S 133 
#define  WMI_VDEV_SUBTYPE_NONE 132 
#define  WMI_VDEV_SUBTYPE_P2P_CLIENT 131 
#define  WMI_VDEV_SUBTYPE_P2P_DEVICE 130 
#define  WMI_VDEV_SUBTYPE_P2P_GO 129 
#define  WMI_VDEV_SUBTYPE_PROXY_STA 128 

__attribute__((used)) static int ath10k_wmi_10_2_4_op_get_vdev_subtype(struct ath10k *ar,
						 enum wmi_vdev_subtype subtype)
{
	switch (subtype) {
	case WMI_VDEV_SUBTYPE_NONE:
		return WMI_VDEV_SUBTYPE_10_2_4_NONE;
	case WMI_VDEV_SUBTYPE_P2P_DEVICE:
		return WMI_VDEV_SUBTYPE_10_2_4_P2P_DEV;
	case WMI_VDEV_SUBTYPE_P2P_CLIENT:
		return WMI_VDEV_SUBTYPE_10_2_4_P2P_CLI;
	case WMI_VDEV_SUBTYPE_P2P_GO:
		return WMI_VDEV_SUBTYPE_10_2_4_P2P_GO;
	case WMI_VDEV_SUBTYPE_PROXY_STA:
		return WMI_VDEV_SUBTYPE_10_2_4_PROXY_STA;
	case WMI_VDEV_SUBTYPE_MESH_11S:
		return WMI_VDEV_SUBTYPE_10_2_4_MESH_11S;
	case WMI_VDEV_SUBTYPE_MESH_NON_11S:
		return -ENOTSUPP;
	}
	return -ENOTSUPP;
}