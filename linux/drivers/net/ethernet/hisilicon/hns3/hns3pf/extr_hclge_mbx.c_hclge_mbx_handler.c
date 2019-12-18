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
struct hclge_dev {TYPE_3__ hw; TYPE_2__* pdev; int /*<<< orphan*/  vport_cfg_mutex; struct hclge_vport* vport; int /*<<< orphan*/  state; } ;
struct hclge_desc {scalar_t__ flag; scalar_t__ data; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_CMDQ_RX_OUTVLD_B ; 
 int /*<<< orphan*/  HCLGE_MAC_ADDR_MC ; 
 int /*<<< orphan*/  HCLGE_MAC_ADDR_UC ; 
#define  HCLGE_MBX_GET_LINK_MODE 149 
#define  HCLGE_MBX_GET_LINK_STATUS 148 
#define  HCLGE_MBX_GET_MEDIA_TYPE 147 
#define  HCLGE_MBX_GET_QDEPTH 146 
#define  HCLGE_MBX_GET_QID_IN_PF 145 
#define  HCLGE_MBX_GET_QINFO 144 
#define  HCLGE_MBX_GET_RSS_KEY 143 
#define  HCLGE_MBX_GET_TCINFO 142 
#define  HCLGE_MBX_GET_VF_FLR_STATUS 141 
#define  HCLGE_MBX_KEEP_ALIVE 140 
#define  HCLGE_MBX_MAP_RING_TO_VECTOR 139 
#define  HCLGE_MBX_NCSI_ERROR 138 
#define  HCLGE_MBX_PUSH_LINK_STATUS 137 
#define  HCLGE_MBX_QUEUE_RESET 136 
#define  HCLGE_MBX_RESET 135 
#define  HCLGE_MBX_SET_ALIVE 134 
#define  HCLGE_MBX_SET_MTU 133 
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
 int /*<<< orphan*/  hclge_get_link_mode (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int hclge_get_queue_id_in_pf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int hclge_get_rss_key (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int hclge_get_vf_media_type (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int hclge_get_vf_queue_depth (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int) ; 
 int hclge_get_vf_queue_info (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int) ; 
 int hclge_get_vf_tcinfo (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int) ; 
 int /*<<< orphan*/  hclge_handle_link_change_event (struct hclge_dev*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int /*<<< orphan*/  hclge_handle_ncsi_error (struct hclge_dev*) ; 
 int hclge_map_unmap_ring_to_vf_vector (struct hclge_vport*,int,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int /*<<< orphan*/  hclge_mbx_reset_vf_queue (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int /*<<< orphan*/  hclge_mbx_ring_ptr_move_crq (struct hclge_cmq_ring*) ; 
 int /*<<< orphan*/  hclge_reset_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int /*<<< orphan*/  hclge_rm_vport_all_mac_table (struct hclge_vport*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_rm_vport_all_vlan_table (struct hclge_vport*,int) ; 
 int hclge_set_vf_alive (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int) ; 
 int hclge_set_vf_mc_mac_addr (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int) ; 
 int hclge_set_vf_mtu (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int hclge_set_vf_promisc_mode (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int hclge_set_vf_uc_mac_addr (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int hclge_set_vf_vlan_cfg (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int /*<<< orphan*/  hclge_vf_keep_alive (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*) ; 
 int /*<<< orphan*/  hclge_write_dev (TYPE_3__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  hnae3_get_bit (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void hclge_mbx_handler(struct hclge_dev *hdev)
{
	struct hclge_cmq_ring *crq = &hdev->hw.cmq.crq;
	struct hclge_mbx_vf_to_pf_cmd *req;
	struct hclge_vport *vport;
	struct hclge_desc *desc;
	unsigned int flag;
	int ret;

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
			ret = hclge_set_vf_uc_mac_addr(vport, req);
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
			ret = hclge_set_vf_vlan_cfg(vport, req);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"PF failed(%d) to config VF's VLAN\n",
					ret);
			break;
		case HCLGE_MBX_SET_ALIVE:
			ret = hclge_set_vf_alive(vport, req, false);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"PF failed(%d) to set VF's ALIVE\n",
					ret);
			break;
		case HCLGE_MBX_GET_QINFO:
			ret = hclge_get_vf_queue_info(vport, req, true);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"PF failed(%d) to get Q info for VF\n",
					ret);
			break;
		case HCLGE_MBX_GET_QDEPTH:
			ret = hclge_get_vf_queue_depth(vport, req, true);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"PF failed(%d) to get Q depth for VF\n",
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
		case HCLGE_MBX_KEEP_ALIVE:
			hclge_vf_keep_alive(vport, req);
			break;
		case HCLGE_MBX_SET_MTU:
			ret = hclge_set_vf_mtu(vport, req);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"VF fail(%d) to set mtu\n", ret);
			break;
		case HCLGE_MBX_GET_QID_IN_PF:
			ret = hclge_get_queue_id_in_pf(vport, req);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"PF failed(%d) to get qid for VF\n",
					ret);
			break;
		case HCLGE_MBX_GET_RSS_KEY:
			ret = hclge_get_rss_key(vport, req);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"PF fail(%d) to get rss key for VF\n",
					ret);
			break;
		case HCLGE_MBX_GET_LINK_MODE:
			hclge_get_link_mode(vport, req);
			break;
		case HCLGE_MBX_GET_VF_FLR_STATUS:
			mutex_lock(&hdev->vport_cfg_mutex);
			hclge_rm_vport_all_mac_table(vport, true,
						     HCLGE_MAC_ADDR_UC);
			hclge_rm_vport_all_mac_table(vport, true,
						     HCLGE_MAC_ADDR_MC);
			hclge_rm_vport_all_vlan_table(vport, true);
			mutex_unlock(&hdev->vport_cfg_mutex);
			break;
		case HCLGE_MBX_GET_MEDIA_TYPE:
			ret = hclge_get_vf_media_type(vport, req);
			if (ret)
				dev_err(&hdev->pdev->dev,
					"PF fail(%d) to media type for VF\n",
					ret);
			break;
		case HCLGE_MBX_PUSH_LINK_STATUS:
			hclge_handle_link_change_event(hdev, req);
			break;
		case HCLGE_MBX_NCSI_ERROR:
			hclge_handle_ncsi_error(hdev);
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