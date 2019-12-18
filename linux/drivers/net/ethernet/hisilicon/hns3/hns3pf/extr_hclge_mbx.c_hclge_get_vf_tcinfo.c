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
typedef  int /*<<< orphan*/  vf_tc_map ;
typedef  int /*<<< orphan*/  u8 ;
struct hnae3_knic_private_info {unsigned int num_tc; } ;
struct TYPE_2__ {struct hnae3_knic_private_info kinfo; } ;
struct hclge_vport {TYPE_1__ nic; } ;
struct hclge_mbx_vf_to_pf_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int hclge_gen_resp_to_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hclge_get_vf_tcinfo(struct hclge_vport *vport,
			       struct hclge_mbx_vf_to_pf_cmd *mbx_req,
			       bool gen_resp)
{
	struct hnae3_knic_private_info *kinfo = &vport->nic.kinfo;
	u8 vf_tc_map = 0;
	unsigned int i;
	int ret;

	for (i = 0; i < kinfo->num_tc; i++)
		vf_tc_map |= BIT(i);

	ret = hclge_gen_resp_to_vf(vport, mbx_req, 0, &vf_tc_map,
				   sizeof(vf_tc_map));

	return ret;
}