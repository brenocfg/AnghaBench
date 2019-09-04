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
struct TYPE_2__ {int vf_id; int sqs_mode; int loopback_supported; int /*<<< orphan*/  node_id; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  tns_mode; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ nic_cfg; } ;
typedef  int /*<<< orphan*/  u8 ;
struct nicpf {int num_vf_en; int /*<<< orphan*/  node; int /*<<< orphan*/ * vf_lmac_map; } ;

/* Variables and functions */
 int NIC_GET_BGX_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int NIC_GET_LMAC_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_READY ; 
 int /*<<< orphan*/  NIC_TNS_BYPASS_MODE ; 
 char* bgx_get_lmac_mac (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  nic_send_msg_to_vf (struct nicpf*,int,union nic_mbx*) ; 

__attribute__((used)) static void nic_mbx_send_ready(struct nicpf *nic, int vf)
{
	union nic_mbx mbx = {};
	int bgx_idx, lmac;
	const char *mac;

	mbx.nic_cfg.msg = NIC_MBOX_MSG_READY;
	mbx.nic_cfg.vf_id = vf;

	mbx.nic_cfg.tns_mode = NIC_TNS_BYPASS_MODE;

	if (vf < nic->num_vf_en) {
		bgx_idx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
		lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);

		mac = bgx_get_lmac_mac(nic->node, bgx_idx, lmac);
		if (mac)
			ether_addr_copy((u8 *)&mbx.nic_cfg.mac_addr, mac);
	}
	mbx.nic_cfg.sqs_mode = (vf >= nic->num_vf_en) ? true : false;
	mbx.nic_cfg.node_id = nic->node;

	mbx.nic_cfg.loopback_supported = vf < nic->num_vf_en;

	nic_send_msg_to_vf(nic, vf, &mbx);
}