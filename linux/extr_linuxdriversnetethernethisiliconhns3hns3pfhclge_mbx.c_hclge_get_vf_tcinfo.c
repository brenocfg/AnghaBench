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
typedef  int /*<<< orphan*/  u8 ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_mbx_vf_to_pf_cmd {int dummy; } ;
struct hclge_dev {int /*<<< orphan*/  hw_tc_map; } ;

/* Variables and functions */
 int hclge_gen_resp_to_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hclge_get_vf_tcinfo(struct hclge_vport *vport,
			       struct hclge_mbx_vf_to_pf_cmd *mbx_req,
			       bool gen_resp)
{
	struct hclge_dev *hdev = vport->back;
	int ret;

	ret = hclge_gen_resp_to_vf(vport, mbx_req, 0, &hdev->hw_tc_map,
				   sizeof(u8));

	return ret;
}