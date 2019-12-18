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
typedef  int /*<<< orphan*/  u16 ;
struct hnae3_ring_chain_node {int /*<<< orphan*/  int_gl_idx; int /*<<< orphan*/  tqp_index; int /*<<< orphan*/  flag; struct hnae3_ring_chain_node* next; } ;
struct hclge_vport {int /*<<< orphan*/  vport_id; struct hclge_dev* back; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct hclge_ctrl_vector_chain_cmd {int int_vector_id; int int_cause_num; int /*<<< orphan*/  vfid; int /*<<< orphan*/ * tqp_type_and_id; } ;
typedef  enum hclge_opcode_type { ____Placeholder_hclge_opcode_type } hclge_opcode_type ;
typedef  enum hclge_cmd_status { ____Placeholder_hclge_cmd_status } hclge_cmd_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HCLGE_INT_GL_IDX_M ; 
 int /*<<< orphan*/  HCLGE_INT_GL_IDX_S ; 
 int /*<<< orphan*/  HCLGE_INT_TYPE_M ; 
 int /*<<< orphan*/  HCLGE_INT_TYPE_S ; 
 int HCLGE_OPC_ADD_RING_TO_VECTOR ; 
 int HCLGE_OPC_DEL_RING_TO_VECTOR ; 
 int /*<<< orphan*/  HCLGE_TQP_ID_M ; 
 int /*<<< orphan*/  HCLGE_TQP_ID_S ; 
 int HCLGE_VECTOR_ELEMENTS_PER_CMD ; 
 int /*<<< orphan*/  HNAE3_RING_GL_IDX_M ; 
 int /*<<< orphan*/  HNAE3_RING_GL_IDX_S ; 
 int /*<<< orphan*/  HNAE3_RING_TYPE_B ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int,int) ; 
 int /*<<< orphan*/  hnae3_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hnae3_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hnae3_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

int hclge_bind_ring_with_vector(struct hclge_vport *vport,
				int vector_id, bool en,
				struct hnae3_ring_chain_node *ring_chain)
{
	struct hclge_dev *hdev = vport->back;
	struct hnae3_ring_chain_node *node;
	struct hclge_desc desc;
	struct hclge_ctrl_vector_chain_cmd *req =
		(struct hclge_ctrl_vector_chain_cmd *)desc.data;
	enum hclge_cmd_status status;
	enum hclge_opcode_type op;
	u16 tqp_type_and_id;
	int i;

	op = en ? HCLGE_OPC_ADD_RING_TO_VECTOR : HCLGE_OPC_DEL_RING_TO_VECTOR;
	hclge_cmd_setup_basic_desc(&desc, op, false);
	req->int_vector_id = vector_id;

	i = 0;
	for (node = ring_chain; node; node = node->next) {
		tqp_type_and_id = le16_to_cpu(req->tqp_type_and_id[i]);
		hnae3_set_field(tqp_type_and_id,  HCLGE_INT_TYPE_M,
				HCLGE_INT_TYPE_S,
				hnae3_get_bit(node->flag, HNAE3_RING_TYPE_B));
		hnae3_set_field(tqp_type_and_id, HCLGE_TQP_ID_M,
				HCLGE_TQP_ID_S, node->tqp_index);
		hnae3_set_field(tqp_type_and_id, HCLGE_INT_GL_IDX_M,
				HCLGE_INT_GL_IDX_S,
				hnae3_get_field(node->int_gl_idx,
						HNAE3_RING_GL_IDX_M,
						HNAE3_RING_GL_IDX_S));
		req->tqp_type_and_id[i] = cpu_to_le16(tqp_type_and_id);
		if (++i >= HCLGE_VECTOR_ELEMENTS_PER_CMD) {
			req->int_cause_num = HCLGE_VECTOR_ELEMENTS_PER_CMD;
			req->vfid = vport->vport_id;

			status = hclge_cmd_send(&hdev->hw, &desc, 1);
			if (status) {
				dev_err(&hdev->pdev->dev,
					"Map TQP fail, status is %d.\n",
					status);
				return -EIO;
			}
			i = 0;

			hclge_cmd_setup_basic_desc(&desc,
						   op,
						   false);
			req->int_vector_id = vector_id;
		}
	}

	if (i > 0) {
		req->int_cause_num = i;
		req->vfid = vport->vport_id;
		status = hclge_cmd_send(&hdev->hw, &desc, 1);
		if (status) {
			dev_err(&hdev->pdev->dev,
				"Map TQP fail, status is %d.\n", status);
			return -EIO;
		}
	}

	return 0;
}