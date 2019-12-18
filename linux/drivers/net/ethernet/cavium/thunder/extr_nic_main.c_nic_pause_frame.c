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
struct TYPE_2__ {int /*<<< orphan*/  fc_tx; int /*<<< orphan*/  fc_rx; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ pfc; } ;
struct pfc {int /*<<< orphan*/  fc_tx; int /*<<< orphan*/  fc_rx; int /*<<< orphan*/  autoneg; scalar_t__ get; } ;
struct nicpf {int num_vf_en; int /*<<< orphan*/  node; int /*<<< orphan*/ * vf_lmac_map; } ;

/* Variables and functions */
 int NIC_GET_BGX_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int NIC_GET_LMAC_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_PFC ; 
 int /*<<< orphan*/  bgx_lmac_get_pfc (int /*<<< orphan*/ ,int,int,struct pfc*) ; 
 int /*<<< orphan*/  bgx_lmac_set_pfc (int /*<<< orphan*/ ,int,int,struct pfc*) ; 
 int /*<<< orphan*/  nic_mbx_send_ack (struct nicpf*,int) ; 
 int /*<<< orphan*/  nic_send_msg_to_vf (struct nicpf*,int,union nic_mbx*) ; 

__attribute__((used)) static void nic_pause_frame(struct nicpf *nic, int vf, struct pfc *cfg)
{
	int bgx, lmac;
	struct pfc pfc;
	union nic_mbx mbx = {};

	if (vf >= nic->num_vf_en)
		return;
	bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
	lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);

	if (cfg->get) {
		bgx_lmac_get_pfc(nic->node, bgx, lmac, &pfc);
		mbx.pfc.msg = NIC_MBOX_MSG_PFC;
		mbx.pfc.autoneg = pfc.autoneg;
		mbx.pfc.fc_rx = pfc.fc_rx;
		mbx.pfc.fc_tx = pfc.fc_tx;
		nic_send_msg_to_vf(nic, vf, &mbx);
	} else {
		bgx_lmac_set_pfc(nic->node, bgx, lmac, cfg);
		nic_mbx_send_ack(nic, vf);
	}
}