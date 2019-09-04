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
struct qed_hwfn {TYPE_1__* mcp_info; } ;
struct TYPE_2__ {int b_block_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qed_hwfn*,char*,char*) ; 

__attribute__((used)) static void qed_mcp_cmd_set_blocking(struct qed_hwfn *p_hwfn, bool block_cmd)
{
	p_hwfn->mcp_info->b_block_cmd = block_cmd;

	DP_INFO(p_hwfn, "%s sending of mailbox commands to the MFW\n",
		block_cmd ? "Block" : "Unblock");
}