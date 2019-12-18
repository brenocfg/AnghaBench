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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {struct qed_bulletin_content* p_virt; } ;
struct qed_vf_info {TYPE_1__ bulletin; } ;
struct qed_mcp_link_state {int /*<<< orphan*/  sfp_tx_fault; int /*<<< orphan*/  partner_adv_pause; int /*<<< orphan*/  partner_rx_flow_ctrl_en; int /*<<< orphan*/  partner_tx_flow_ctrl_en; int /*<<< orphan*/  partner_adv_speed; int /*<<< orphan*/  pfc_enabled; int /*<<< orphan*/  parallel_detection; int /*<<< orphan*/  an_complete; int /*<<< orphan*/  an; int /*<<< orphan*/  full_duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  link_up; } ;
struct TYPE_6__ {int /*<<< orphan*/  forced_tx; int /*<<< orphan*/  forced_rx; int /*<<< orphan*/  autoneg; } ;
struct TYPE_5__ {int /*<<< orphan*/  forced_speed; int /*<<< orphan*/  advertised_speeds; int /*<<< orphan*/  autoneg; } ;
struct qed_mcp_link_params {int /*<<< orphan*/  loopback_mode; TYPE_3__ pause; TYPE_2__ speed; } ;
struct qed_mcp_link_capabilities {int /*<<< orphan*/  speed_capabilities; } ;
struct qed_hwfn {int dummy; } ;
struct qed_bulletin_content {int /*<<< orphan*/  capability_speed; int /*<<< orphan*/  sfp_tx_fault; int /*<<< orphan*/  partner_adv_pause; int /*<<< orphan*/  partner_rx_flow_ctrl_en; int /*<<< orphan*/  partner_tx_flow_ctrl_en; int /*<<< orphan*/  partner_adv_speed; int /*<<< orphan*/  pfc_enabled; int /*<<< orphan*/  parallel_detection; int /*<<< orphan*/  autoneg_complete; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  full_duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  link_up; int /*<<< orphan*/  req_loopback; int /*<<< orphan*/  req_forced_tx; int /*<<< orphan*/  req_forced_rx; int /*<<< orphan*/  req_autoneg_pause; int /*<<< orphan*/  req_forced_speed; int /*<<< orphan*/  req_adv_speed; int /*<<< orphan*/  req_autoneg; } ;

/* Variables and functions */
 struct qed_vf_info* qed_iov_get_vf_info (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qed_iov_set_link(struct qed_hwfn *p_hwfn,
			     u16 vfid,
			     struct qed_mcp_link_params *params,
			     struct qed_mcp_link_state *link,
			     struct qed_mcp_link_capabilities *p_caps)
{
	struct qed_vf_info *p_vf = qed_iov_get_vf_info(p_hwfn,
						       vfid,
						       false);
	struct qed_bulletin_content *p_bulletin;

	if (!p_vf)
		return;

	p_bulletin = p_vf->bulletin.p_virt;
	p_bulletin->req_autoneg = params->speed.autoneg;
	p_bulletin->req_adv_speed = params->speed.advertised_speeds;
	p_bulletin->req_forced_speed = params->speed.forced_speed;
	p_bulletin->req_autoneg_pause = params->pause.autoneg;
	p_bulletin->req_forced_rx = params->pause.forced_rx;
	p_bulletin->req_forced_tx = params->pause.forced_tx;
	p_bulletin->req_loopback = params->loopback_mode;

	p_bulletin->link_up = link->link_up;
	p_bulletin->speed = link->speed;
	p_bulletin->full_duplex = link->full_duplex;
	p_bulletin->autoneg = link->an;
	p_bulletin->autoneg_complete = link->an_complete;
	p_bulletin->parallel_detection = link->parallel_detection;
	p_bulletin->pfc_enabled = link->pfc_enabled;
	p_bulletin->partner_adv_speed = link->partner_adv_speed;
	p_bulletin->partner_tx_flow_ctrl_en = link->partner_tx_flow_ctrl_en;
	p_bulletin->partner_rx_flow_ctrl_en = link->partner_rx_flow_ctrl_en;
	p_bulletin->partner_adv_pause = link->partner_adv_pause;
	p_bulletin->sfp_tx_fault = link->sfp_tx_fault;

	p_bulletin->capability_speed = p_caps->speed_capabilities;
}