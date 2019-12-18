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
typedef  int /*<<< orphan*/  u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  rel_pf_id; } ;
struct qed_arfs_config_params {scalar_t__ mode; scalar_t__ ipv6; scalar_t__ ipv4; scalar_t__ udp; scalar_t__ tcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ QED_FILTER_CONFIG_MODE_DISABLE ; 
 int /*<<< orphan*/  QED_MSG_SP ; 
 int /*<<< orphan*/  qed_arfs_mode_to_hsi (scalar_t__) ; 
 int /*<<< orphan*/  qed_gft_config (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_gft_disable (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 

void qed_arfs_mode_configure(struct qed_hwfn *p_hwfn,
			     struct qed_ptt *p_ptt,
			     struct qed_arfs_config_params *p_cfg_params)
{
	if (p_cfg_params->mode != QED_FILTER_CONFIG_MODE_DISABLE) {
		qed_gft_config(p_hwfn, p_ptt, p_hwfn->rel_pf_id,
			       p_cfg_params->tcp,
			       p_cfg_params->udp,
			       p_cfg_params->ipv4,
			       p_cfg_params->ipv6,
			       qed_arfs_mode_to_hsi(p_cfg_params->mode));
		DP_VERBOSE(p_hwfn,
			   QED_MSG_SP,
			   "Configured Filtering: tcp = %s, udp = %s, ipv4 = %s, ipv6 =%s mode=%08x\n",
			   p_cfg_params->tcp ? "Enable" : "Disable",
			   p_cfg_params->udp ? "Enable" : "Disable",
			   p_cfg_params->ipv4 ? "Enable" : "Disable",
			   p_cfg_params->ipv6 ? "Enable" : "Disable",
			   (u32)p_cfg_params->mode);
	} else {
		DP_VERBOSE(p_hwfn, QED_MSG_SP, "Disabled Filtering\n");
		qed_gft_disable(p_hwfn, p_ptt, p_hwfn->rel_pf_id);
	}
}