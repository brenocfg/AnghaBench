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
struct mac_driver {int /*<<< orphan*/  (* config_max_frame_length ) (struct mac_driver*,int) ;} ;
struct hns_mac_cb {int max_frm; } ;

/* Variables and functions */
 int ECHILD ; 
 int EINVAL ; 
 int ETH_FCS_LEN ; 
 int ETH_FRAME_LEN ; 
 int ETH_HLEN ; 
 int HNS_RCB_RING_MAX_BD_PER_PKT ; 
 int VLAN_HLEN ; 
 struct mac_driver* hns_mac_get_drv (struct hns_mac_cb*) ; 
 int /*<<< orphan*/  stub1 (struct mac_driver*,int) ; 

int hns_mac_set_mtu(struct hns_mac_cb *mac_cb, u32 new_mtu, u32 buf_size)
{
	struct mac_driver *drv = hns_mac_get_drv(mac_cb);
	u32 new_frm = new_mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;

	if (new_frm > HNS_RCB_RING_MAX_BD_PER_PKT * buf_size)
		return -EINVAL;

	if (!drv->config_max_frame_length)
		return -ECHILD;

	/* adjust max frame to be at least the size of a standard frame */
	if (new_frm < (ETH_FRAME_LEN + ETH_FCS_LEN + VLAN_HLEN))
		new_frm = (ETH_FRAME_LEN + ETH_FCS_LEN + VLAN_HLEN);

	drv->config_max_frame_length(drv, new_frm);

	mac_cb->max_frm = new_frm;

	return 0;
}