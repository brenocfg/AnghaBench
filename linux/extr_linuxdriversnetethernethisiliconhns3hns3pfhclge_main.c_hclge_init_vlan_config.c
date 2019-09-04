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
struct hnae3_handle {int dummy; } ;
struct TYPE_6__ {int strip_tag1_en; int strip_tag2_en; int vlan1_vlan_prionly; int vlan2_vlan_prionly; } ;
struct TYPE_5__ {int accept_tag1; int accept_untag1; int accept_tag2; int accept_untag2; int insert_tag1_en; int insert_tag2_en; scalar_t__ default_tag2; scalar_t__ default_tag1; } ;
struct hclge_vport {struct hnae3_handle nic; TYPE_3__ rxvlan_cfg; TYPE_2__ txvlan_cfg; } ;
struct TYPE_4__ {int rx_in_fst_vlan_type; int rx_in_sec_vlan_type; int rx_ot_fst_vlan_type; int rx_ot_sec_vlan_type; int tx_ot_vlan_type; int tx_in_vlan_type; } ;
struct hclge_dev {int num_alloc_vport; struct hclge_vport* vport; TYPE_1__ vlan_type_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  HCLGE_FILTER_TYPE_PORT ; 
 int /*<<< orphan*/  HCLGE_FILTER_TYPE_VF ; 
 int hclge_set_vlan_filter (struct hnae3_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hclge_set_vlan_filter_ctrl (struct hclge_dev*,int /*<<< orphan*/ ,int) ; 
 int hclge_set_vlan_protocol_type (struct hclge_dev*) ; 
 int hclge_set_vlan_rx_offload_cfg (struct hclge_vport*) ; 
 int hclge_set_vlan_tx_offload_cfg (struct hclge_vport*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_init_vlan_config(struct hclge_dev *hdev)
{
#define HCLGE_DEF_VLAN_TYPE		0x8100

	struct hnae3_handle *handle;
	struct hclge_vport *vport;
	int ret;
	int i;

	ret = hclge_set_vlan_filter_ctrl(hdev, HCLGE_FILTER_TYPE_VF, true);
	if (ret)
		return ret;

	ret = hclge_set_vlan_filter_ctrl(hdev, HCLGE_FILTER_TYPE_PORT, true);
	if (ret)
		return ret;

	hdev->vlan_type_cfg.rx_in_fst_vlan_type = HCLGE_DEF_VLAN_TYPE;
	hdev->vlan_type_cfg.rx_in_sec_vlan_type = HCLGE_DEF_VLAN_TYPE;
	hdev->vlan_type_cfg.rx_ot_fst_vlan_type = HCLGE_DEF_VLAN_TYPE;
	hdev->vlan_type_cfg.rx_ot_sec_vlan_type = HCLGE_DEF_VLAN_TYPE;
	hdev->vlan_type_cfg.tx_ot_vlan_type = HCLGE_DEF_VLAN_TYPE;
	hdev->vlan_type_cfg.tx_in_vlan_type = HCLGE_DEF_VLAN_TYPE;

	ret = hclge_set_vlan_protocol_type(hdev);
	if (ret)
		return ret;

	for (i = 0; i < hdev->num_alloc_vport; i++) {
		vport = &hdev->vport[i];
		vport->txvlan_cfg.accept_tag1 = true;
		vport->txvlan_cfg.accept_untag1 = true;

		/* accept_tag2 and accept_untag2 are not supported on
		 * pdev revision(0x20), new revision support them. The
		 * value of this two fields will not return error when driver
		 * send command to fireware in revision(0x20).
		 * This two fields can not configured by user.
		 */
		vport->txvlan_cfg.accept_tag2 = true;
		vport->txvlan_cfg.accept_untag2 = true;

		vport->txvlan_cfg.insert_tag1_en = false;
		vport->txvlan_cfg.insert_tag2_en = false;
		vport->txvlan_cfg.default_tag1 = 0;
		vport->txvlan_cfg.default_tag2 = 0;

		ret = hclge_set_vlan_tx_offload_cfg(vport);
		if (ret)
			return ret;

		vport->rxvlan_cfg.strip_tag1_en = false;
		vport->rxvlan_cfg.strip_tag2_en = true;
		vport->rxvlan_cfg.vlan1_vlan_prionly = false;
		vport->rxvlan_cfg.vlan2_vlan_prionly = false;

		ret = hclge_set_vlan_rx_offload_cfg(vport);
		if (ret)
			return ret;
	}

	handle = &hdev->vport[0].nic;
	return hclge_set_vlan_filter(handle, htons(ETH_P_8021Q), 0, false);
}