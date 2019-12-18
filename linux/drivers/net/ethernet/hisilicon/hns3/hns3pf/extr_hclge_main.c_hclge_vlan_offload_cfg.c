#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int strip_tag1_en; int strip_tag2_en; int rx_vlan_offload_en; int vlan1_vlan_prionly; int vlan2_vlan_prionly; } ;
struct TYPE_3__ {int accept_tag1; int insert_tag1_en; int accept_untag1; int accept_tag2; int accept_untag2; int insert_tag2_en; scalar_t__ default_tag2; scalar_t__ default_tag1; } ;
struct hclge_vport {TYPE_2__ rxvlan_cfg; TYPE_1__ txvlan_cfg; } ;

/* Variables and functions */
 scalar_t__ HNAE3_PORT_BASE_VLAN_DISABLE ; 
 int hclge_set_vlan_rx_offload_cfg (struct hclge_vport*) ; 
 int hclge_set_vlan_tx_offload_cfg (struct hclge_vport*) ; 

__attribute__((used)) static int hclge_vlan_offload_cfg(struct hclge_vport *vport,
				  u16 port_base_vlan_state,
				  u16 vlan_tag)
{
	int ret;

	if (port_base_vlan_state == HNAE3_PORT_BASE_VLAN_DISABLE) {
		vport->txvlan_cfg.accept_tag1 = true;
		vport->txvlan_cfg.insert_tag1_en = false;
		vport->txvlan_cfg.default_tag1 = 0;
	} else {
		vport->txvlan_cfg.accept_tag1 = false;
		vport->txvlan_cfg.insert_tag1_en = true;
		vport->txvlan_cfg.default_tag1 = vlan_tag;
	}

	vport->txvlan_cfg.accept_untag1 = true;

	/* accept_tag2 and accept_untag2 are not supported on
	 * pdev revision(0x20), new revision support them,
	 * this two fields can not be configured by user.
	 */
	vport->txvlan_cfg.accept_tag2 = true;
	vport->txvlan_cfg.accept_untag2 = true;
	vport->txvlan_cfg.insert_tag2_en = false;
	vport->txvlan_cfg.default_tag2 = 0;

	if (port_base_vlan_state == HNAE3_PORT_BASE_VLAN_DISABLE) {
		vport->rxvlan_cfg.strip_tag1_en = false;
		vport->rxvlan_cfg.strip_tag2_en =
				vport->rxvlan_cfg.rx_vlan_offload_en;
	} else {
		vport->rxvlan_cfg.strip_tag1_en =
				vport->rxvlan_cfg.rx_vlan_offload_en;
		vport->rxvlan_cfg.strip_tag2_en = true;
	}
	vport->rxvlan_cfg.vlan1_vlan_prionly = false;
	vport->rxvlan_cfg.vlan2_vlan_prionly = false;

	ret = hclge_set_vlan_tx_offload_cfg(vport);
	if (ret)
		return ret;

	return hclge_set_vlan_rx_offload_cfg(vport);
}