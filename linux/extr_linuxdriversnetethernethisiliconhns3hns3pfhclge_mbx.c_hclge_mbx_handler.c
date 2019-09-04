#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hclge_vport {int dummy; } ;
struct hclge_mbx_vf_to_pf_cmd {int* msg; size_t mbx_src_vfid; } ;
struct hclge_cmq_ring {size_t next_to_use; struct hclge_desc* desc; } ;
struct TYPE_5__ {struct hclge_cmq_ring crq; } ;
struct TYPE_7__ {TYPE_1__ cmq; } ;
struct hclge_dev {TYPE_3__ hw; TYPE_2__* pdev; struct hclge_vport* vport; int /*<<< orphan*/  state; } ;
struct hclge_desc {scalar_t__ flag; scalar_t__ data; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_CMDQ_RX_OUTVLD_B ; 
#define  HCLGE_MBX_GET_LINK_STATUS 138 
#define  HCLGE_MBX_GET_QINFO 137 
#define  HCLGE_MBX_GET_TCINFO 136 
#define  HCLGE_MBX_MAP_RING_TO_VECTOR 135 
#define  HCLGE_MBX_QUEUE_RESET 134 
#define  HCLGE_MBX_RESET 133 
#define  HCLGE_MBX_SET_MULTICAST 132 
#define  HCLGE_MBX_SET_PROMISC_MODE 131 
#define  HCLGE_MBX_SET_UNICAST 130 
#define  HCLGE_MBX_SET_VLAN 129 
#define  HCLGE_MBX_UNMAP_RING_TO_VECTOR 128 
 int /*<<< orphan*/  HCLGE_NIC_CRQ_HEAD_REG ; 
 int /*<<< orphan*/  HCLGE_STATE_CMD_DISABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  hclge_cmd_crq_empty (TYPE_3__*) ; 
 int hclge_get_link_info (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int hclge_get_vf_queue_info (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int) ; 
 int hclge_get_vf_tcinfo (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int) ; 
 int hclge_map_unmap_ring_to_vf_vector (struct hclge_vport*,int,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int /*<<< orphan*/  hclge_mbx_reset_vf_queue (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int /*<<< orphan*/  hclge_mbx_ring_ptr_move_crq (struct hclge_cmq_ring*) ; 
 int /*<<< orphan*/  hclge_reset_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int hclge_set_vf_mc_mac_addr (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int) ; 
 int hclge_set_vf_promisc_mode (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int hclge_set_vf_uc_mac_addr (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int) ; 
 int hclge_set_vf_vlan_cfg (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int) ; 
 int /*<<< orphan*/  hclge_write_dev (TYPE_3__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  hnae3_get_bit (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void hclge_mbx_handler(struct hclge_dev *hdev)
{
	struct hclge_cmq_ring *crq = &hdev->hw.cmq.crq;
	struct hclge_mbx_vf_to_pf_cmd *req;
	struct hclge_vport *vport;
	struct hclge_desc *desc;
	int ret, flag;

	/* handle all the mailbox requests in the queue */
	while (!hclge_cmd_crq_empty(&hdev->hw)) {
		if (test_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state)) {
			dev_warn(&hdev->pdev->dev,
				 "command queue needs re-initializing\n");
			return;
		}

		desc = &crq->desc[crq->next_to_use];
		req = (struct hclge_mbx_vf_to_pf_cmd *)desc->data;

		flag = le16_to_cpu(crq->desc[crq->next_to_use].flag);
		if (unlikely(!hnae3_get_bit(flag, HCLGE_CMDQ_RX_OUTVLD_B))) {
			dev_warn(&hdev->pdev->dev,
				 "dropped invalid mailbox message, code = %d\n",
				 req->msg[0]);

			/* dropping/not processing this invalid message */
			crq->desc[crq->next_to_use].flag = 0;
			hclge_mbx_ring_ptr_move_crq(crq);
			continue;
		}

		vport = &hdev->vport[req->mbx_src_vfid];

		switch (req->msg[0]) {
		case HCLGE_MBX_MAP_RING_TO_VECTOR:
			ret = hclge_map_unmap_ring_to_vf_vector(vport, true,
								req);
			break;
		case HCLGE_MBX_UNMAP_RING_TO_VECTOR:
			ret = hclge_map_unmap_ring_to_vf_vector(vport, false,
								req);
			break;
		case HCLGE_MBX_SET_PROMISC_MODE:
			ret = hclge_set_vf_promisc_mode(vport, req);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"PF fail(%d) to set VF promisc mode\n",
					ret);
			break;
		case HCLGE_MBX_SET_UNICAST:
			ret = hclge_set_vf_uc_mac_addr(vport, req, true);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"PF fail(%d) to set VF UC MAC Addr\n",
					ret);
			break;
		case HCLGE_MBX_SET_MULTICAST:
			ret = hclge_set_vf_mc_mac_addr(vport, req, false);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"PF fail(%d) to set VF MC MAC Addr\n",
					ret);
			break;
		case HCLGE_MBX_SET_VLAN:
			ret = hclge_set_vf_vlan_cfg(vport, req, false);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"PF failed(%d) to config VF's VLAN\n",
					ret);
			break;
		case HCLGE_MBX_GET_QINFO:
			ret = hclge_get_vf_queue_info(vport, req, true);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"PF failed(%d) to get Q info for VF\n",
					ret);
			break;
		case HCLGE_MBX_GET_TCINFO:
			ret = hclge_get_vf_tcinfo(vport, req, true);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"PF failed(%d) to get TC info for VF\n",
					ret);
			break;
		case HCLGE_MBX_GET_LINK_STATUS:
			ret = hclge_get_link_info(vport, req);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"PF fail(%d) to get link stat for VF\n",
					ret);
			break;
		case HCLGE_MBX_QUEUE_RESET:
			hclge_mbx_reset_vf_queue(vport, req);
			break;
		case HCLGE_MBX_RESET:
			hclge_reset_vf(vport, req);
			break;
		default:
			dev_err(&hdev->pdev->dev,
				"un-supported mailbox message, code = %d\n",
				req->msg[0]);
			break;
		}
		crq->desc[crq->next_to_use].flag = 0;
		hclge_mbx_ring_ptr_move_crq(crq);
	}

	/* Write back CMDQ_RQ header pointer, M7 need this pointer */
	hclge_write_dev(&hdev->hw, HCLGE_NIC_CRQ_HEAD_REG, crq->next_to_use);
}