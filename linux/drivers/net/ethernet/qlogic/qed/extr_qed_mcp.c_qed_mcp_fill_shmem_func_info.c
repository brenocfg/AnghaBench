#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  void* u16 ;
struct qed_ptt {int dummy; } ;
struct qed_mcp_function_info {int pause_on_host; int wwn_port; int wwn_node; void* ovlan; void** mac; int /*<<< orphan*/  bandwidth_max; int /*<<< orphan*/  bandwidth_min; int /*<<< orphan*/  protocol; void* mtu; } ;
struct TYPE_6__ {scalar_t__ b_wol_support; } ;
struct qed_hwfn {TYPE_3__ hw_info; TYPE_2__* cdev; TYPE_1__* mcp_info; } ;
struct public_func {int config; int mac_upper; int mac_lower; int ovlan_stag; scalar_t__ mtu_size; scalar_t__ fcoe_wwn_node_name_upper; scalar_t__ fcoe_wwn_node_name_lower; scalar_t__ fcoe_wwn_port_name_upper; scalar_t__ fcoe_wwn_port_name_lower; } ;
struct TYPE_5__ {void* wol_config; int /*<<< orphan*/  wol_mac; } ;
struct TYPE_4__ {struct qed_mcp_function_info func_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,scalar_t__) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,void*,void*,void*,void*,int,int,void*,void*) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OS_WOL ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int FUNC_MF_CFG_OV_STAG_MASK ; 
 int FUNC_MF_CFG_PAUSE_ON_HOST_RING ; 
 int FUNC_MF_CFG_PROTOCOL_MASK ; 
 scalar_t__ FW_MSG_CODE_OS_WOL_SUPPORTED ; 
 int /*<<< orphan*/  MCP_PF_ID (struct qed_hwfn*) ; 
 int NETIF_MSG_IFUP ; 
 int QED_MSG_SP ; 
 scalar_t__ QED_OV_WOL_DEFAULT ; 
 scalar_t__ QED_WOL_SUPPORT_NONE ; 
 scalar_t__ QED_WOL_SUPPORT_PME ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ) ; 
 int qed_mcp_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  qed_mcp_get_shmem_func (struct qed_hwfn*,struct qed_ptt*,struct public_func*,int /*<<< orphan*/ ) ; 
 scalar_t__ qed_mcp_get_shmem_proto (struct qed_hwfn*,struct public_func*,struct qed_ptt*,int /*<<< orphan*/ *) ; 
 scalar_t__ qed_mcp_is_init (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_read_pf_bandwidth (struct qed_hwfn*,struct public_func*) ; 

int qed_mcp_fill_shmem_func_info(struct qed_hwfn *p_hwfn,
				 struct qed_ptt *p_ptt)
{
	struct qed_mcp_function_info *info;
	struct public_func shmem_info;

	qed_mcp_get_shmem_func(p_hwfn, p_ptt, &shmem_info, MCP_PF_ID(p_hwfn));
	info = &p_hwfn->mcp_info->func_info;

	info->pause_on_host = (shmem_info.config &
			       FUNC_MF_CFG_PAUSE_ON_HOST_RING) ? 1 : 0;

	if (qed_mcp_get_shmem_proto(p_hwfn, &shmem_info, p_ptt,
				    &info->protocol)) {
		DP_ERR(p_hwfn, "Unknown personality %08x\n",
		       (u32)(shmem_info.config & FUNC_MF_CFG_PROTOCOL_MASK));
		return -EINVAL;
	}

	qed_read_pf_bandwidth(p_hwfn, &shmem_info);

	if (shmem_info.mac_upper || shmem_info.mac_lower) {
		info->mac[0] = (u8)(shmem_info.mac_upper >> 8);
		info->mac[1] = (u8)(shmem_info.mac_upper);
		info->mac[2] = (u8)(shmem_info.mac_lower >> 24);
		info->mac[3] = (u8)(shmem_info.mac_lower >> 16);
		info->mac[4] = (u8)(shmem_info.mac_lower >> 8);
		info->mac[5] = (u8)(shmem_info.mac_lower);

		/* Store primary MAC for later possible WoL */
		memcpy(&p_hwfn->cdev->wol_mac, info->mac, ETH_ALEN);
	} else {
		DP_NOTICE(p_hwfn, "MAC is 0 in shmem\n");
	}

	info->wwn_port = (u64)shmem_info.fcoe_wwn_port_name_lower |
			 (((u64)shmem_info.fcoe_wwn_port_name_upper) << 32);
	info->wwn_node = (u64)shmem_info.fcoe_wwn_node_name_lower |
			 (((u64)shmem_info.fcoe_wwn_node_name_upper) << 32);

	info->ovlan = (u16)(shmem_info.ovlan_stag & FUNC_MF_CFG_OV_STAG_MASK);

	info->mtu = (u16)shmem_info.mtu_size;

	p_hwfn->hw_info.b_wol_support = QED_WOL_SUPPORT_NONE;
	p_hwfn->cdev->wol_config = (u8)QED_OV_WOL_DEFAULT;
	if (qed_mcp_is_init(p_hwfn)) {
		u32 resp = 0, param = 0;
		int rc;

		rc = qed_mcp_cmd(p_hwfn, p_ptt,
				 DRV_MSG_CODE_OS_WOL, 0, &resp, &param);
		if (rc)
			return rc;
		if (resp == FW_MSG_CODE_OS_WOL_SUPPORTED)
			p_hwfn->hw_info.b_wol_support = QED_WOL_SUPPORT_PME;
	}

	DP_VERBOSE(p_hwfn, (QED_MSG_SP | NETIF_MSG_IFUP),
		   "Read configuration from shmem: pause_on_host %02x protocol %02x BW [%02x - %02x] MAC %02x:%02x:%02x:%02x:%02x:%02x wwn port %llx node %llx ovlan %04x wol %02x\n",
		info->pause_on_host, info->protocol,
		info->bandwidth_min, info->bandwidth_max,
		info->mac[0], info->mac[1], info->mac[2],
		info->mac[3], info->mac[4], info->mac[5],
		info->wwn_port, info->wwn_node,
		info->ovlan, (u8)p_hwfn->hw_info.b_wol_support);

	return 0;
}