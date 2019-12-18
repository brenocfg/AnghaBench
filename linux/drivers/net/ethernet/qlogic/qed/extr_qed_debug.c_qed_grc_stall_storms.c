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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
typedef  enum dbg_storms { ____Placeholder_dbg_storms } dbg_storms ;
struct TYPE_2__ {scalar_t__ sem_fast_mem_addr; } ;

/* Variables and functions */
 size_t MAX_DBG_STORMS ; 
 scalar_t__ SEM_FAST_REG_STALL_0_BB_K2 ; 
 int /*<<< orphan*/  STALL_DELAY_MS ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_grc_is_storm_included (struct qed_hwfn*,int) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,scalar_t__,int) ; 
 TYPE_1__* s_storm_defs ; 

__attribute__((used)) static void qed_grc_stall_storms(struct qed_hwfn *p_hwfn,
				 struct qed_ptt *p_ptt, bool stall)
{
	u32 reg_addr;
	u8 storm_id;

	for (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++) {
		if (!qed_grc_is_storm_included(p_hwfn,
					       (enum dbg_storms)storm_id))
			continue;

		reg_addr = s_storm_defs[storm_id].sem_fast_mem_addr +
		    SEM_FAST_REG_STALL_0_BB_K2;
		qed_wr(p_hwfn, p_ptt, reg_addr, stall ? 1 : 0);
	}

	msleep(STALL_DELAY_MS);
}