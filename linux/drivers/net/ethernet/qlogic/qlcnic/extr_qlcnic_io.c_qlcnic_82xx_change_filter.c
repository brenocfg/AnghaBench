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
typedef  int u64 ;
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct qlcnic_vlan_req {int /*<<< orphan*/  vlan_id; } ;
struct qlcnic_nic_req {int /*<<< orphan*/ * words; void* req_hdr; void* qhdr; } ;
struct qlcnic_mac_req {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  op; } ;
struct qlcnic_host_tx_ring {size_t producer; int /*<<< orphan*/  num_desc; struct cmd_desc_type0* desc_head; } ;
struct qlcnic_adapter {scalar_t__ portnum; } ;
struct cmd_desc_type0 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  QLCNIC_MAC_ADD ; 
 int QLCNIC_MAC_EVENT ; 
 int /*<<< orphan*/  QLCNIC_MAC_VLAN_ADD ; 
 int QLCNIC_REQUEST ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le64 (int) ; 
 size_t get_next_index (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qlcnic_nic_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_mb () ; 

void qlcnic_82xx_change_filter(struct qlcnic_adapter *adapter, u64 *uaddr,
			       u16 vlan_id, struct qlcnic_host_tx_ring *tx_ring)
{
	struct cmd_desc_type0 *hwdesc;
	struct qlcnic_nic_req *req;
	struct qlcnic_mac_req *mac_req;
	struct qlcnic_vlan_req *vlan_req;
	u32 producer;
	u64 word;

	producer = tx_ring->producer;
	hwdesc = &tx_ring->desc_head[tx_ring->producer];

	req = (struct qlcnic_nic_req *)hwdesc;
	memset(req, 0, sizeof(struct qlcnic_nic_req));
	req->qhdr = cpu_to_le64(QLCNIC_REQUEST << 23);

	word = QLCNIC_MAC_EVENT | ((u64)(adapter->portnum) << 16);
	req->req_hdr = cpu_to_le64(word);

	mac_req = (struct qlcnic_mac_req *)&(req->words[0]);
	mac_req->op = vlan_id ? QLCNIC_MAC_VLAN_ADD : QLCNIC_MAC_ADD;
	memcpy(mac_req->mac_addr, uaddr, ETH_ALEN);

	vlan_req = (struct qlcnic_vlan_req *)&req->words[1];
	vlan_req->vlan_id = cpu_to_le16(vlan_id);

	tx_ring->producer = get_next_index(producer, tx_ring->num_desc);
	smp_mb();
}