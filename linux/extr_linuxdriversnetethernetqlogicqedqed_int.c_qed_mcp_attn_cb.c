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
struct qed_hwfn {int /*<<< orphan*/  p_dpc_ptt; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCP_REG_CPU_EVENT_MASK ; 
 int /*<<< orphan*/  MCP_REG_CPU_STATE ; 
 int /*<<< orphan*/  qed_rd (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qed_mcp_attn_cb(struct qed_hwfn *p_hwfn)
{
	u32 tmp = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt, MCP_REG_CPU_STATE);

	/* This might occur on certain instances; Log it once then mask it */
	DP_INFO(p_hwfn->cdev, "MCP_REG_CPU_STATE: %08x - Masking...\n",
		tmp);
	qed_wr(p_hwfn, p_hwfn->p_dpc_ptt, MCP_REG_CPU_EVENT_MASK,
	       0xffffffff);

	return 0;
}