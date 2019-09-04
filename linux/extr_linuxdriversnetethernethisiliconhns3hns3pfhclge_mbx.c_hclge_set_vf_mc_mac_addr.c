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
typedef  int u8 ;
struct hclge_vport {int vport_id; struct hclge_dev* back; } ;
struct hclge_mbx_vf_to_pf_cmd {int* msg; } ;
struct hclge_dev {int mta_mac_sel_type; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int HCLGE_MBX_MAC_VLAN_MC_ADD ; 
 int HCLGE_MBX_MAC_VLAN_MC_FUNC_MTA_ENABLE ; 
 int HCLGE_MBX_MAC_VLAN_MC_REMOVE ; 
 int HCLGE_MBX_MAC_VLAN_MTA_STATUS_UPDATE ; 
 int HCLGE_MBX_MAC_VLAN_MTA_TYPE_READ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_add_mc_addr_common (struct hclge_vport*,int const*) ; 
 int hclge_cfg_func_mta_filter (struct hclge_dev*,int,int) ; 
 int /*<<< orphan*/  hclge_gen_resp_to_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int,int*,int) ; 
 int hclge_rm_mc_addr_common (struct hclge_vport*,int const*) ; 
 int hclge_set_vf_mc_mta_status (struct hclge_vport*,int*,int,int) ; 

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
	} else if (mbx_req->msg[1] == HCLGE_MBX_MAC_VLAN_MC_REMOVE) {
		status = hclge_rm_mc_addr_common(vport, mac_addr);
	} else if (mbx_req->msg[1] == HCLGE_MBX_MAC_VLAN_MC_FUNC_MTA_ENABLE) {
		u8 func_id = vport->vport_id;
		bool enable = mbx_req->msg[2];

		status = hclge_cfg_func_mta_filter(hdev, func_id, enable);
	} else if (mbx_req->msg[1] == HCLGE_MBX_MAC_VLAN_MTA_TYPE_READ) {
		resp_data = hdev->mta_mac_sel_type;
		resp_len = sizeof(u8);
		gen_resp = true;
		status = 0;
	} else if (mbx_req->msg[1] == HCLGE_MBX_MAC_VLAN_MTA_STATUS_UPDATE) {
		/* mta status update msg format
		 * msg[2.6 : 2.0]  msg index
		 * msg[2.7]        msg is end
		 * msg[15 : 3]     mta status bits[103 : 0]
		 */
		bool is_end = (mbx_req->msg[2] & 0x80) ? true : false;

		status = hclge_set_vf_mc_mta_status(vport, &mbx_req->msg[3],
						    mbx_req->msg[2] & 0x7F,
						    is_end);
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