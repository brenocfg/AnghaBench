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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct qlcnic_vlan_req {int /*<<< orphan*/  vlan_id; } ;
struct qlcnic_nic_req {int /*<<< orphan*/ * words; void* req_hdr; void* qhdr; } ;
struct qlcnic_mac_req {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  op; } ;
struct qlcnic_adapter {scalar_t__ portnum; } ;
struct cmd_desc_type0 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int QLCNIC_MAC_EVENT ; 
 int QLCNIC_REQUEST ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qlcnic_nic_req*,int /*<<< orphan*/ ,int) ; 
 int qlcnic_send_cmd_descs (struct qlcnic_adapter*,struct cmd_desc_type0*,int) ; 

int qlcnic_82xx_sre_macaddr_change(struct qlcnic_adapter *adapter, u8 *addr,
				   u16 vlan_id, u8 op)
{
	struct qlcnic_nic_req req;
	struct qlcnic_mac_req *mac_req;
	struct qlcnic_vlan_req *vlan_req;
	u64 word;

	memset(&req, 0, sizeof(struct qlcnic_nic_req));
	req.qhdr = cpu_to_le64(QLCNIC_REQUEST << 23);

	word = QLCNIC_MAC_EVENT | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	mac_req = (struct qlcnic_mac_req *)&req.words[0];
	mac_req->op = op;
	memcpy(mac_req->mac_addr, addr, ETH_ALEN);

	vlan_req = (struct qlcnic_vlan_req *)&req.words[1];
	vlan_req->vlan_id = cpu_to_le16(vlan_id);

	return qlcnic_send_cmd_descs(adapter, (struct cmd_desc_type0 *)&req, 1);
}