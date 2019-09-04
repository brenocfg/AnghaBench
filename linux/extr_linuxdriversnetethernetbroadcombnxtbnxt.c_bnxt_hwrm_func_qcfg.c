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
typedef  int u16 ;
struct hwrm_func_qcfg_output {int port_partition_type; scalar_t__ evb_mode; int /*<<< orphan*/  max_mtu_configured; int /*<<< orphan*/  flags; } ;
struct hwrm_func_qcfg_input {int /*<<< orphan*/  fid; int /*<<< orphan*/  member_0; } ;
struct bnxt {int port_partition_type; int hwrm_spec_code; int /*<<< orphan*/  hwrm_cmd_lock; void* max_mtu; int /*<<< orphan*/  br_mode; int /*<<< orphan*/  flags; int /*<<< orphan*/  fw_cap; struct hwrm_func_qcfg_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_FLAG_MULTI_HOST ; 
 int /*<<< orphan*/  BNXT_FW_CAP_DCBX_AGENT ; 
 int /*<<< orphan*/  BNXT_FW_CAP_LLDP_AGENT ; 
 void* BNXT_MAX_MTU ; 
 scalar_t__ BNXT_PF (struct bnxt*) ; 
 int /*<<< orphan*/  BRIDGE_MODE_UNDEF ; 
 int /*<<< orphan*/  BRIDGE_MODE_VEB ; 
 int /*<<< orphan*/  BRIDGE_MODE_VEPA ; 
 scalar_t__ FUNC_QCFG_RESP_EVB_MODE_VEB ; 
 scalar_t__ FUNC_QCFG_RESP_EVB_MODE_VEPA ; 
 int FUNC_QCFG_RESP_FLAGS_FW_DCBX_AGENT_ENABLED ; 
 int FUNC_QCFG_RESP_FLAGS_FW_LLDP_AGENT_ENABLED ; 
 int FUNC_QCFG_RESP_FLAGS_MULTI_HOST ; 
#define  FUNC_QCFG_RESP_PORT_PARTITION_TYPE_NPAR1_0 130 
#define  FUNC_QCFG_RESP_PORT_PARTITION_TYPE_NPAR1_5 129 
#define  FUNC_QCFG_RESP_PORT_PARTITION_TYPE_NPAR2_0 128 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_FUNC_QCFG ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_func_qcfg_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_func_qcfg_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_hwrm_func_qcfg(struct bnxt *bp)
{
	struct hwrm_func_qcfg_input req = {0};
	struct hwrm_func_qcfg_output *resp = bp->hwrm_cmd_resp_addr;
	u16 flags;
	int rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_QCFG, -1, -1);
	req.fid = cpu_to_le16(0xffff);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (rc)
		goto func_qcfg_exit;

#ifdef CONFIG_BNXT_SRIOV
	if (BNXT_VF(bp)) {
		struct bnxt_vf_info *vf = &bp->vf;

		vf->vlan = le16_to_cpu(resp->vlan) & VLAN_VID_MASK;
	}
#endif
	flags = le16_to_cpu(resp->flags);
	if (flags & (FUNC_QCFG_RESP_FLAGS_FW_DCBX_AGENT_ENABLED |
		     FUNC_QCFG_RESP_FLAGS_FW_LLDP_AGENT_ENABLED)) {
		bp->fw_cap |= BNXT_FW_CAP_LLDP_AGENT;
		if (flags & FUNC_QCFG_RESP_FLAGS_FW_DCBX_AGENT_ENABLED)
			bp->fw_cap |= BNXT_FW_CAP_DCBX_AGENT;
	}
	if (BNXT_PF(bp) && (flags & FUNC_QCFG_RESP_FLAGS_MULTI_HOST))
		bp->flags |= BNXT_FLAG_MULTI_HOST;

	switch (resp->port_partition_type) {
	case FUNC_QCFG_RESP_PORT_PARTITION_TYPE_NPAR1_0:
	case FUNC_QCFG_RESP_PORT_PARTITION_TYPE_NPAR1_5:
	case FUNC_QCFG_RESP_PORT_PARTITION_TYPE_NPAR2_0:
		bp->port_partition_type = resp->port_partition_type;
		break;
	}
	if (bp->hwrm_spec_code < 0x10707 ||
	    resp->evb_mode == FUNC_QCFG_RESP_EVB_MODE_VEB)
		bp->br_mode = BRIDGE_MODE_VEB;
	else if (resp->evb_mode == FUNC_QCFG_RESP_EVB_MODE_VEPA)
		bp->br_mode = BRIDGE_MODE_VEPA;
	else
		bp->br_mode = BRIDGE_MODE_UNDEF;

	bp->max_mtu = le16_to_cpu(resp->max_mtu_configured);
	if (!bp->max_mtu)
		bp->max_mtu = BNXT_MAX_MTU;

func_qcfg_exit:
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}