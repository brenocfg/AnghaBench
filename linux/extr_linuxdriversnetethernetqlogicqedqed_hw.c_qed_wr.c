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
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 int /*<<< orphan*/  REG_WR (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_set_ptt (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 

void qed_wr(struct qed_hwfn *p_hwfn,
	    struct qed_ptt *p_ptt,
	    u32 hw_addr, u32 val)
{
	u32 bar_addr = qed_set_ptt(p_hwfn, p_ptt, hw_addr);

	REG_WR(p_hwfn, bar_addr, val);
	DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
		   "bar_addr 0x%x, hw_addr 0x%x, val 0x%x\n",
		   bar_addr, hw_addr, val);
}