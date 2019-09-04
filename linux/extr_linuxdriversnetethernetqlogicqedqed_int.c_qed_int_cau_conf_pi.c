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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {scalar_t__ hw_init_done; int /*<<< orphan*/  cdev; } ;
struct cau_pi_entry {int /*<<< orphan*/  prod; } ;
typedef  enum qed_coalescing_fsm { ____Placeholder_qed_coalescing_fsm } qed_coalescing_fsm ;

/* Variables and functions */
 int /*<<< orphan*/  CAU_PI_ENTRY_FSM_SEL ; 
 int /*<<< orphan*/  CAU_PI_ENTRY_PI_TIMESET ; 
 scalar_t__ CAU_REG_PI_MEMORY ; 
 scalar_t__ CAU_REG_PI_MEMORY_RT_OFFSET ; 
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int PIS_PER_SB_E4 ; 
 int QED_COAL_RX_STATE_MACHINE ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STORE_RT_REG (struct qed_hwfn*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct cau_pi_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,scalar_t__,int) ; 

__attribute__((used)) static void qed_int_cau_conf_pi(struct qed_hwfn *p_hwfn,
				struct qed_ptt *p_ptt,
				u16 igu_sb_id,
				u32 pi_index,
				enum qed_coalescing_fsm coalescing_fsm,
				u8 timeset)
{
	struct cau_pi_entry pi_entry;
	u32 sb_offset, pi_offset;

	if (IS_VF(p_hwfn->cdev))
		return;

	sb_offset = igu_sb_id * PIS_PER_SB_E4;
	memset(&pi_entry, 0, sizeof(struct cau_pi_entry));

	SET_FIELD(pi_entry.prod, CAU_PI_ENTRY_PI_TIMESET, timeset);
	if (coalescing_fsm == QED_COAL_RX_STATE_MACHINE)
		SET_FIELD(pi_entry.prod, CAU_PI_ENTRY_FSM_SEL, 0);
	else
		SET_FIELD(pi_entry.prod, CAU_PI_ENTRY_FSM_SEL, 1);

	pi_offset = sb_offset + pi_index;
	if (p_hwfn->hw_init_done) {
		qed_wr(p_hwfn, p_ptt,
		       CAU_REG_PI_MEMORY + pi_offset * sizeof(u32),
		       *((u32 *)&(pi_entry)));
	} else {
		STORE_RT_REG(p_hwfn,
			     CAU_REG_PI_MEMORY_RT_OFFSET + pi_offset,
			     *((u32 *)&(pi_entry)));
	}
}