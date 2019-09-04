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
typedef  int /*<<< orphan*/  u16 ;
struct qed_mcp_mb_params {int dummy; } ;
struct qed_mcp_cmd_elem {int /*<<< orphan*/  list; int /*<<< orphan*/  expected_seq_num; struct qed_mcp_mb_params* p_mb_params; } ;
struct qed_hwfn {TYPE_1__* mcp_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct qed_mcp_cmd_elem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct qed_mcp_cmd_elem *
qed_mcp_cmd_add_elem(struct qed_hwfn *p_hwfn,
		     struct qed_mcp_mb_params *p_mb_params,
		     u16 expected_seq_num)
{
	struct qed_mcp_cmd_elem *p_cmd_elem = NULL;

	p_cmd_elem = kzalloc(sizeof(*p_cmd_elem), GFP_ATOMIC);
	if (!p_cmd_elem)
		goto out;

	p_cmd_elem->p_mb_params = p_mb_params;
	p_cmd_elem->expected_seq_num = expected_seq_num;
	list_add(&p_cmd_elem->list, &p_hwfn->mcp_info->cmd_list);
out:
	return p_cmd_elem;
}