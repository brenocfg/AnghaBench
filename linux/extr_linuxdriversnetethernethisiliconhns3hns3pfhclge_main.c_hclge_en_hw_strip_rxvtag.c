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
struct hnae3_handle {int dummy; } ;
struct TYPE_2__ {int strip_tag1_en; int strip_tag2_en; int vlan1_vlan_prionly; int vlan2_vlan_prionly; } ;
struct hclge_vport {TYPE_1__ rxvlan_cfg; } ;

/* Variables and functions */
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_set_vlan_rx_offload_cfg (struct hclge_vport*) ; 

int hclge_en_hw_strip_rxvtag(struct hnae3_handle *handle, bool enable)
{
	struct hclge_vport *vport = hclge_get_vport(handle);

	vport->rxvlan_cfg.strip_tag1_en = false;
	vport->rxvlan_cfg.strip_tag2_en = enable;
	vport->rxvlan_cfg.vlan1_vlan_prionly = false;
	vport->rxvlan_cfg.vlan2_vlan_prionly = false;

	return hclge_set_vlan_rx_offload_cfg(vport);
}