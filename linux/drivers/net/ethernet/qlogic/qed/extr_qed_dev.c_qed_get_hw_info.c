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
struct qed_ptt {int dummy; } ;
struct TYPE_4__ {scalar_t__ ovlan; int personality; int multi_tc_roce_en; int num_active_tc; int /*<<< orphan*/  mtu; int /*<<< orphan*/  num_hw_tc; int /*<<< orphan*/  hw_mac_addr; } ;
struct qed_hwfn {TYPE_3__* mcp_info; TYPE_1__ hw_info; } ;
typedef  enum qed_pci_personality { ____Placeholder_qed_pci_personality } qed_pci_personality ;
struct TYPE_5__ {scalar_t__ ovlan; int protocol; int /*<<< orphan*/  mtu; int /*<<< orphan*/  mac; } ;
struct TYPE_6__ {TYPE_2__ func_info; } ;

/* Variables and functions */
 scalar_t__ IS_LEAD_HWFN (struct qed_hwfn*) ; 
 int /*<<< orphan*/  NUM_PHYS_TCS_4PORT_K2 ; 
 scalar_t__ QED_IS_ROCE_PERSONALITY (struct qed_hwfn*) ; 
 scalar_t__ QED_MCP_VLAN_UNSET ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_get_eee_caps (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_get_num_funcs (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_hw_get_nvm_info (struct qed_hwfn*,struct qed_ptt*) ; 
 int qed_hw_get_resc (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_hw_info_port_num (struct qed_hwfn*,struct qed_ptt*) ; 
 int qed_int_igu_read_cam (struct qed_hwfn*,struct qed_ptt*) ; 
 int qed_iov_hw_info (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_mcp_cmd_port_init (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_mcp_get_capabilities (struct qed_hwfn*,struct qed_ptt*) ; 
 scalar_t__ qed_mcp_is_init (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_mcp_read_ufp_config (struct qed_hwfn*,struct qed_ptt*) ; 

__attribute__((used)) static int
qed_get_hw_info(struct qed_hwfn *p_hwfn,
		struct qed_ptt *p_ptt,
		enum qed_pci_personality personality)
{
	int rc;

	/* Since all information is common, only first hwfns should do this */
	if (IS_LEAD_HWFN(p_hwfn)) {
		rc = qed_iov_hw_info(p_hwfn);
		if (rc)
			return rc;
	}

	if (IS_LEAD_HWFN(p_hwfn))
		qed_hw_info_port_num(p_hwfn, p_ptt);

	qed_mcp_get_capabilities(p_hwfn, p_ptt);

	qed_hw_get_nvm_info(p_hwfn, p_ptt);

	rc = qed_int_igu_read_cam(p_hwfn, p_ptt);
	if (rc)
		return rc;

	if (qed_mcp_is_init(p_hwfn))
		ether_addr_copy(p_hwfn->hw_info.hw_mac_addr,
				p_hwfn->mcp_info->func_info.mac);
	else
		eth_random_addr(p_hwfn->hw_info.hw_mac_addr);

	if (qed_mcp_is_init(p_hwfn)) {
		if (p_hwfn->mcp_info->func_info.ovlan != QED_MCP_VLAN_UNSET)
			p_hwfn->hw_info.ovlan =
				p_hwfn->mcp_info->func_info.ovlan;

		qed_mcp_cmd_port_init(p_hwfn, p_ptt);

		qed_get_eee_caps(p_hwfn, p_ptt);

		qed_mcp_read_ufp_config(p_hwfn, p_ptt);
	}

	if (qed_mcp_is_init(p_hwfn)) {
		enum qed_pci_personality protocol;

		protocol = p_hwfn->mcp_info->func_info.protocol;
		p_hwfn->hw_info.personality = protocol;
	}

	if (QED_IS_ROCE_PERSONALITY(p_hwfn))
		p_hwfn->hw_info.multi_tc_roce_en = 1;

	p_hwfn->hw_info.num_hw_tc = NUM_PHYS_TCS_4PORT_K2;
	p_hwfn->hw_info.num_active_tc = 1;

	qed_get_num_funcs(p_hwfn, p_ptt);

	if (qed_mcp_is_init(p_hwfn))
		p_hwfn->hw_info.mtu = p_hwfn->mcp_info->func_info.mtu;

	return qed_hw_get_resc(p_hwfn, p_ptt);
}