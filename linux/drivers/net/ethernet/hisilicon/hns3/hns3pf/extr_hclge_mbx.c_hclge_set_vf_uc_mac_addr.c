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
struct hclge_mbx_vf_to_pf_cmd {int mbx_need_resp; int /*<<< orphan*/ * msg; } ;
struct hclge_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HCLGE_MAC_ADDR_UC ; 
 int /*<<< orphan*/  HCLGE_MBX_MAC_VLAN_UC_ADD ; 
 int /*<<< orphan*/  HCLGE_MBX_MAC_VLAN_UC_MODIFY ; 
 int /*<<< orphan*/  HCLGE_MBX_MAC_VLAN_UC_REMOVE ; 
 int HCLGE_MBX_NEED_RESP_BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int hclge_add_uc_addr_common (struct hclge_vport*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hclge_add_vport_mac_table (struct hclge_vport*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_gen_resp_to_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hclge_rm_uc_addr_common (struct hclge_vport*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hclge_rm_vport_mac_table (struct hclge_vport*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_set_vf_uc_mac_addr(struct hclge_vport *vport,
				    struct hclge_mbx_vf_to_pf_cmd *mbx_req)
{
	const u8 *mac_addr = (const u8 *)(&mbx_req->msg[2]);
	struct hclge_dev *hdev = vport->back;
	int status;

	if (mbx_req->msg[1] == HCLGE_MBX_MAC_VLAN_UC_MODIFY) {
		const u8 *old_addr = (const u8 *)(&mbx_req->msg[8]);

		hclge_rm_uc_addr_common(vport, old_addr);
		status = hclge_add_uc_addr_common(vport, mac_addr);
		if (status) {
			hclge_add_uc_addr_common(vport, old_addr);
		} else {
			hclge_rm_vport_mac_table(vport, mac_addr,
						 false, HCLGE_MAC_ADDR_UC);
			hclge_add_vport_mac_table(vport, mac_addr,
						  HCLGE_MAC_ADDR_UC);
		}
	} else if (mbx_req->msg[1] == HCLGE_MBX_MAC_VLAN_UC_ADD) {
		status = hclge_add_uc_addr_common(vport, mac_addr);
		if (!status)
			hclge_add_vport_mac_table(vport, mac_addr,
						  HCLGE_MAC_ADDR_UC);
	} else if (mbx_req->msg[1] == HCLGE_MBX_MAC_VLAN_UC_REMOVE) {
		status = hclge_rm_uc_addr_common(vport, mac_addr);
		if (!status)
			hclge_rm_vport_mac_table(vport, mac_addr,
						 false, HCLGE_MAC_ADDR_UC);
	} else {
		dev_err(&hdev->pdev->dev,
			"failed to set unicast mac addr, unknown subcode %d\n",
			mbx_req->msg[1]);
		return -EIO;
	}

	if (mbx_req->mbx_need_resp & HCLGE_MBX_NEED_RESP_BIT)
		hclge_gen_resp_to_vf(vport, mbx_req, status, NULL, 0);

	return 0;
}