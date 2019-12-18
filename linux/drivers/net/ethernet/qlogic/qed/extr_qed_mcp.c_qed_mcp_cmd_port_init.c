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
typedef  int /*<<< orphan*/  u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {TYPE_1__* mcp_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_addr; int /*<<< orphan*/  public_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFW_PORT (struct qed_hwfn*) ; 
 int /*<<< orphan*/  PUBLIC_PORT ; 
 int /*<<< orphan*/  QED_MSG_SP ; 
 int /*<<< orphan*/  SECTION_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECTION_OFFSIZE_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 

void qed_mcp_cmd_port_init(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	u32 addr = SECTION_OFFSIZE_ADDR(p_hwfn->mcp_info->public_base,
					PUBLIC_PORT);
	u32 mfw_mb_offsize = qed_rd(p_hwfn, p_ptt, addr);

	p_hwfn->mcp_info->port_addr = SECTION_ADDR(mfw_mb_offsize,
						   MFW_PORT(p_hwfn));
	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "port_addr = 0x%x, port_id 0x%02x\n",
		   p_hwfn->mcp_info->port_addr, MFW_PORT(p_hwfn));
}