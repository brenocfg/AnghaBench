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
typedef  int /*<<< orphan*/  u8 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 scalar_t__ QED_IS_BB (int /*<<< orphan*/ ) ; 
 int qed_mcp_config_vf_msix_ah (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int qed_mcp_config_vf_msix_bb (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qed_mcp_config_vf_msix(struct qed_hwfn *p_hwfn,
			   struct qed_ptt *p_ptt, u8 vf_id, u8 num)
{
	if (QED_IS_BB(p_hwfn->cdev))
		return qed_mcp_config_vf_msix_bb(p_hwfn, p_ptt, vf_id, num);
	else
		return qed_mcp_config_vf_msix_ah(p_hwfn, p_ptt, num);
}