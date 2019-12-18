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
struct qed_hwfn {scalar_t__ dbg_user_info; } ;
struct dbg_tools_user_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct dbg_tools_user_data *
qed_dbg_get_user_data(struct qed_hwfn *p_hwfn)
{
	return (struct dbg_tools_user_data *)p_hwfn->dbg_user_info;
}