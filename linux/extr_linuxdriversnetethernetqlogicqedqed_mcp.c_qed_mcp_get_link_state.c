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
struct qed_mcp_link_state {int dummy; } ;
struct qed_hwfn {TYPE_1__* mcp_info; } ;
struct TYPE_2__ {struct qed_mcp_link_state link_output; } ;

/* Variables and functions */

struct qed_mcp_link_state
*qed_mcp_get_link_state(struct qed_hwfn *p_hwfn)
{
	if (!p_hwfn || !p_hwfn->mcp_info)
		return NULL;
	return &p_hwfn->mcp_info->link_output;
}