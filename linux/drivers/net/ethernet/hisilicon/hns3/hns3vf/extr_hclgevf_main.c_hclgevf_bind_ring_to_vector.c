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
typedef  void* u8 ;
struct hnae3_ring_chain_node {int tqp_index; struct hnae3_ring_chain_node* next; int /*<<< orphan*/  int_gl_idx; int /*<<< orphan*/  flag; } ;
struct hnae3_handle {int dummy; } ;
struct hclgevf_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclgevf_desc {scalar_t__ data; } ;
struct hclge_mbx_vf_to_pf_cmd {int* msg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_OPC_MBX_VF_TO_PF ; 
 void* HCLGE_MBX_MAP_RING_TO_VECTOR ; 
 int HCLGE_MBX_RING_MAP_BASIC_MSG_NUM ; 
 int HCLGE_MBX_RING_NODE_VARIABLE_NUM ; 
 void* HCLGE_MBX_UNMAP_RING_TO_VECTOR ; 
 int HCLGE_MBX_VF_MSG_DATA_NUM ; 
 int /*<<< orphan*/  HNAE3_RING_GL_IDX_M ; 
 int /*<<< orphan*/  HNAE3_RING_GL_IDX_S ; 
 int /*<<< orphan*/  HNAE3_RING_TYPE_B ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_cmd_send (int /*<<< orphan*/ *,struct hclgevf_desc*,int) ; 
 int /*<<< orphan*/  hclgevf_cmd_setup_basic_desc (struct hclgevf_desc*,int /*<<< orphan*/ ,int) ; 
 int hnae3_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hnae3_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclgevf_bind_ring_to_vector(struct hnae3_handle *handle, bool en,
				       int vector_id,
				       struct hnae3_ring_chain_node *ring_chain)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	struct hnae3_ring_chain_node *node;
	struct hclge_mbx_vf_to_pf_cmd *req;
	struct hclgevf_desc desc;
	int i = 0;
	int status;
	u8 type;

	req = (struct hclge_mbx_vf_to_pf_cmd *)desc.data;
	type = en ? HCLGE_MBX_MAP_RING_TO_VECTOR :
		HCLGE_MBX_UNMAP_RING_TO_VECTOR;

	for (node = ring_chain; node; node = node->next) {
		int idx_offset = HCLGE_MBX_RING_MAP_BASIC_MSG_NUM +
					HCLGE_MBX_RING_NODE_VARIABLE_NUM * i;

		if (i == 0) {
			hclgevf_cmd_setup_basic_desc(&desc,
						     HCLGEVF_OPC_MBX_VF_TO_PF,
						     false);
			req->msg[0] = type;
			req->msg[1] = vector_id;
		}

		req->msg[idx_offset] =
				hnae3_get_bit(node->flag, HNAE3_RING_TYPE_B);
		req->msg[idx_offset + 1] = node->tqp_index;
		req->msg[idx_offset + 2] = hnae3_get_field(node->int_gl_idx,
							   HNAE3_RING_GL_IDX_M,
							   HNAE3_RING_GL_IDX_S);

		i++;
		if ((i == (HCLGE_MBX_VF_MSG_DATA_NUM -
		     HCLGE_MBX_RING_MAP_BASIC_MSG_NUM) /
		     HCLGE_MBX_RING_NODE_VARIABLE_NUM) ||
		    !node->next) {
			req->msg[2] = i;

			status = hclgevf_cmd_send(&hdev->hw, &desc, 1);
			if (status) {
				dev_err(&hdev->pdev->dev,
					"Map TQP fail, status is %d.\n",
					status);
				return status;
			}
			i = 0;
			hclgevf_cmd_setup_basic_desc(&desc,
						     HCLGEVF_OPC_MBX_VF_TO_PF,
						     false);
			req->msg[0] = type;
			req->msg[1] = vector_id;
		}
	}

	return 0;
}