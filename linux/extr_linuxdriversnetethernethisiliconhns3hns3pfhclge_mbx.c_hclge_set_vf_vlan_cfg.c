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
typedef  int /*<<< orphan*/  vlan ;
typedef  int /*<<< orphan*/  u16 ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hnae3_handle nic; } ;
struct hclge_mbx_vf_to_pf_cmd {scalar_t__* msg; } ;
typedef  int /*<<< orphan*/  proto ;

/* Variables and functions */
 scalar_t__ HCLGE_MBX_VLAN_FILTER ; 
 scalar_t__ HCLGE_MBX_VLAN_RX_OFF_CFG ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int hclge_en_hw_strip_rxvtag (struct hnae3_handle*,int) ; 
 int hclge_gen_resp_to_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hclge_set_vlan_filter (struct hnae3_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 

__attribute__((used)) static int hclge_set_vf_vlan_cfg(struct hclge_vport *vport,
				 struct hclge_mbx_vf_to_pf_cmd *mbx_req,
				 bool gen_resp)
{
	int status = 0;

	if (mbx_req->msg[1] == HCLGE_MBX_VLAN_FILTER) {
		struct hnae3_handle *handle = &vport->nic;
		u16 vlan, proto;
		bool is_kill;

		is_kill = !!mbx_req->msg[2];
		memcpy(&vlan, &mbx_req->msg[3], sizeof(vlan));
		memcpy(&proto, &mbx_req->msg[5], sizeof(proto));
		status = hclge_set_vlan_filter(handle, cpu_to_be16(proto),
					       vlan, is_kill);
	} else if (mbx_req->msg[1] == HCLGE_MBX_VLAN_RX_OFF_CFG) {
		struct hnae3_handle *handle = &vport->nic;
		bool en = mbx_req->msg[2] ? true : false;

		status = hclge_en_hw_strip_rxvtag(handle, en);
	}

	if (gen_resp)
		status = hclge_gen_resp_to_vf(vport, mbx_req, status, NULL, 0);

	return status;
}