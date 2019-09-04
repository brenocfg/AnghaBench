#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct netxen_adapter {scalar_t__ portnum; } ;
struct cmd_desc_type0 {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * words; void* req_hdr; void* qhdr; } ;
typedef  TYPE_1__ nx_nic_req_t ;
struct TYPE_5__ {unsigned int op; int /*<<< orphan*/  mac_addr; } ;
typedef  TYPE_2__ nx_mac_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int NX_MAC_EVENT ; 
 int NX_NIC_REQUEST ; 
 void* cpu_to_le64 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int netxen_send_cmd_descs (struct netxen_adapter*,struct cmd_desc_type0*,int) ; 

__attribute__((used)) static int
nx_p3_sre_macaddr_change(struct netxen_adapter *adapter, u8 *addr, unsigned op)
{
	nx_nic_req_t req;
	nx_mac_req_t *mac_req;
	u64 word;

	memset(&req, 0, sizeof(nx_nic_req_t));
	req.qhdr = cpu_to_le64(NX_NIC_REQUEST << 23);

	word = NX_MAC_EVENT | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	mac_req = (nx_mac_req_t *)&req.words[0];
	mac_req->op = op;
	memcpy(mac_req->mac_addr, addr, ETH_ALEN);

	return netxen_send_cmd_descs(adapter, (struct cmd_desc_type0 *)&req, 1);
}