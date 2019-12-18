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
typedef  int /*<<< orphan*/  u8 ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_mbx_vf_to_pf_cmd {int /*<<< orphan*/ * msg; } ;
struct hclge_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HCLGE_MAC_ADDR_MC ; 
 int /*<<< orphan*/  HCLGE_MBX_MAC_VLAN_MC_ADD ; 
 int /*<<< orphan*/  HCLGE_MBX_MAC_VLAN_MC_REMOVE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int hclge_add_mc_addr_common (struct hclge_vport*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hclge_add_vport_mac_table (struct hclge_vport*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_gen_resp_to_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hclge_rm_mc_addr_common (struct hclge_vport*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hclge_rm_vport_mac_table (struct hclge_vport*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_set_vf_mc_mac_addr(struct hclge_vport *vport,
				    struct hclge_mbx_vf_to_pf_cmd *mbx_req,
				    bool gen_resp)
{
	const u8 *mac_addr = (const u8 *)(&mbx_req->msg[2]);
	struct hclge_dev *hdev = vport->back;
	u8 resp_len = 0;
	u8 resp_data;
	int status;

	if (mbx_req->msg[1] == HCLGE_MBX_MAC_VLAN_MC_ADD) {
		status = hclge_add_mc_addr_common(vport, mac_addr);
		if (!status)
			hclge_add_vport_mac_table(vport, mac_addr,
						  HCLGE_MAC_ADDR_MC);
	} else if (mbx_req->msg[1] == HCLGE_MBX_MAC_VLAN_MC_REMOVE) {
		status = hclge_rm_mc_addr_common(vport, mac_addr);
		if (!status)
			hclge_rm_vport_mac_table(vport, mac_addr,
						 false, HCLGE_MAC_ADDR_MC);
	} else {
		dev_err(&hdev->pdev->dev,
			"failed to set mcast mac addr, unknown subcode %d\n",
			mbx_req->msg[1]);
		return -EIO;
	}

	if (gen_resp)
		hclge_gen_resp_to_vf(vport, mbx_req, status,
				     &resp_data, resp_len);

	return 0;
}