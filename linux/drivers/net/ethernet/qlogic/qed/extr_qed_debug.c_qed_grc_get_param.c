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
struct TYPE_2__ {int /*<<< orphan*/ * param_val; } ;
struct dbg_tools_data {TYPE_1__ grc; } ;
struct qed_hwfn {struct dbg_tools_data dbg_info; } ;
typedef  enum dbg_grc_params { ____Placeholder_dbg_grc_params } dbg_grc_params ;

/* Variables and functions */

__attribute__((used)) static u32 qed_grc_get_param(struct qed_hwfn *p_hwfn,
			     enum dbg_grc_params grc_param)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;

	return dev_data->grc.param_val[grc_param];
}