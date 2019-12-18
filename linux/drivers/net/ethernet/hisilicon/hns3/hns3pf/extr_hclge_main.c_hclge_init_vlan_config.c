#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct hnae3_handle {int /*<<< orphan*/  netdev_flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  vlan_tag; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; TYPE_3__ vlan_info; } ;
struct hclge_vport {TYPE_4__ port_base_vlan_cfg; int /*<<< orphan*/  vport_id; struct hnae3_handle nic; } ;
struct TYPE_6__ {void* tx_in_vlan_type; void* tx_ot_vlan_type; void* rx_ot_sec_vlan_type; void* rx_ot_fst_vlan_type; void* rx_in_sec_vlan_type; void* rx_in_fst_vlan_type; } ;
struct hclge_dev {int num_alloc_vport; struct hclge_vport* vport; TYPE_2__ vlan_type_cfg; TYPE_1__* pdev; } ;
struct TYPE_5__ {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 void* HCLGE_DEF_VLAN_TYPE ; 
 int /*<<< orphan*/  HCLGE_FILTER_FE_EGRESS ; 
 int /*<<< orphan*/  HCLGE_FILTER_FE_EGRESS_V1_B ; 
 int /*<<< orphan*/  HCLGE_FILTER_FE_INGRESS ; 
 int /*<<< orphan*/  HCLGE_FILTER_TYPE_PORT ; 
 int /*<<< orphan*/  HCLGE_FILTER_TYPE_VF ; 
 int /*<<< orphan*/  HNAE3_VLAN_FLTR ; 
 int hclge_set_vlan_filter (struct hnae3_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hclge_set_vlan_filter_ctrl (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int hclge_set_vlan_protocol_type (struct hclge_dev*) ; 
 int hclge_vlan_offload_cfg (struct hclge_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_init_vlan_config(struct hclge_dev *hdev)
{
#define HCLGE_DEF_VLAN_TYPE		0x8100

	struct hnae3_handle *handle = &hdev->vport[0].nic;
	struct hclge_vport *vport;
	int ret;
	int i;

	if (hdev->pdev->revision >= 0x21) {
		/* for revision 0x21, vf vlan filter is per function */
		for (i = 0; i < hdev->num_alloc_vport; i++) {
			vport = &hdev->vport[i];
			ret = hclge_set_vlan_filter_ctrl(hdev,
							 HCLGE_FILTER_TYPE_VF,
							 HCLGE_FILTER_FE_EGRESS,
							 true,
							 vport->vport_id);
			if (ret)
				return ret;
		}

		ret = hclge_set_vlan_filter_ctrl(hdev, HCLGE_FILTER_TYPE_PORT,
						 HCLGE_FILTER_FE_INGRESS, true,
						 0);
		if (ret)
			return ret;
	} else {
		ret = hclge_set_vlan_filter_ctrl(hdev, HCLGE_FILTER_TYPE_VF,
						 HCLGE_FILTER_FE_EGRESS_V1_B,
						 true, 0);
		if (ret)
			return ret;
	}

	handle->netdev_flags |= HNAE3_VLAN_FLTR;

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
		u16 vlan_tag;

		vport = &hdev->vport[i];
		vlan_tag = vport->port_base_vlan_cfg.vlan_info.vlan_tag;

		ret = hclge_vlan_offload_cfg(vport,
					     vport->port_base_vlan_cfg.state,
					     vlan_tag);
		if (ret)
			return ret;
	}

	return hclge_set_vlan_filter(handle, htons(ETH_P_8021Q), 0, false);
}