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
struct qed_mcp_cmd_elem {int /*<<< orphan*/  list; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qed_mcp_cmd_elem*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qed_mcp_cmd_del_elem(struct qed_hwfn *p_hwfn,
				 struct qed_mcp_cmd_elem *p_cmd_elem)
{
	list_del(&p_cmd_elem->list);
	kfree(p_cmd_elem);
}