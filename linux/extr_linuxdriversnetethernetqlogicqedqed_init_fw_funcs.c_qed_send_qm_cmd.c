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
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QM_REG_SDMCMDADDR ; 
 int /*<<< orphan*/  QM_REG_SDMCMDDATALSB ; 
 int /*<<< orphan*/  QM_REG_SDMCMDDATAMSB ; 
 int /*<<< orphan*/  QM_REG_SDMCMDGO ; 
 int qed_poll_on_qm_cmd_ready (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool qed_send_qm_cmd(struct qed_hwfn *p_hwfn,
			    struct qed_ptt *p_ptt,
			    u32 cmd_addr, u32 cmd_data_lsb, u32 cmd_data_msb)
{
	if (!qed_poll_on_qm_cmd_ready(p_hwfn, p_ptt))
		return false;

	qed_wr(p_hwfn, p_ptt, QM_REG_SDMCMDADDR, cmd_addr);
	qed_wr(p_hwfn, p_ptt, QM_REG_SDMCMDDATALSB, cmd_data_lsb);
	qed_wr(p_hwfn, p_ptt, QM_REG_SDMCMDDATAMSB, cmd_data_msb);
	qed_wr(p_hwfn, p_ptt, QM_REG_SDMCMDGO, 1);
	qed_wr(p_hwfn, p_ptt, QM_REG_SDMCMDGO, 0);

	return qed_poll_on_qm_cmd_ready(p_hwfn, p_ptt);
}