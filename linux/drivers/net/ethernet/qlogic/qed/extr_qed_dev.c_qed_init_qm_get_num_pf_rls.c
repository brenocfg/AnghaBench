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
typedef  scalar_t__ u16 ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 scalar_t__ NUM_DEFAULT_RLS ; 
 int /*<<< orphan*/  QED_RL ; 
 int /*<<< orphan*/  QED_VPORT ; 
 int /*<<< orphan*/  RESC_NUM (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 scalar_t__ min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qed_init_qm_get_num_vfs (struct qed_hwfn*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static u16 qed_init_qm_get_num_pf_rls(struct qed_hwfn *p_hwfn)
{
	u16 num_pf_rls, num_vfs = qed_init_qm_get_num_vfs(p_hwfn);

	/* num RLs can't exceed resource amount of rls or vports */
	num_pf_rls = (u16) min_t(u32, RESC_NUM(p_hwfn, QED_RL),
				 RESC_NUM(p_hwfn, QED_VPORT));

	/* Make sure after we reserve there's something left */
	if (num_pf_rls < num_vfs + NUM_DEFAULT_RLS)
		return 0;

	/* subtract rls necessary for VFs and one default one for the PF */
	num_pf_rls -= num_vfs + NUM_DEFAULT_RLS;

	return num_pf_rls;
}