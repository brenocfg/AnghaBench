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
typedef  int /*<<< orphan*/  u16 ;
struct hclge_query_ppu_pf_other_int_dfx_cmd {int /*<<< orphan*/  over_8bd_no_fe_qid; int /*<<< orphan*/  over_8bd_no_fe_vf_id; } ;
struct hclge_dev {int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_PPU_PF_OTHER_INT_DFX ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_query_over_8bd_err_info(struct hclge_dev *hdev, u16 *vf_id,
					 u16 *q_id)
{
	struct hclge_query_ppu_pf_other_int_dfx_cmd *req;
	struct hclge_desc desc;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_PPU_PF_OTHER_INT_DFX, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		return ret;

	req = (struct hclge_query_ppu_pf_other_int_dfx_cmd *)desc.data;
	*vf_id = le16_to_cpu(req->over_8bd_no_fe_vf_id);
	*q_id = le16_to_cpu(req->over_8bd_no_fe_qid);

	return 0;
}