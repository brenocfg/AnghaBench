#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/ * param_val; } ;
struct dbg_tools_data {size_t chip_id; TYPE_1__ grc; } ;
struct qed_hwfn {struct dbg_tools_data dbg_info; } ;
struct TYPE_4__ {int /*<<< orphan*/ * default_val; int /*<<< orphan*/  is_persistent; } ;

/* Variables and functions */
 size_t MAX_DBG_GRC_PARAMS ; 
 TYPE_2__* s_grc_param_defs ; 

void qed_dbg_grc_set_params_default(struct qed_hwfn *p_hwfn)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 i;

	for (i = 0; i < MAX_DBG_GRC_PARAMS; i++)
		if (!s_grc_param_defs[i].is_persistent)
			dev_data->grc.param_val[i] =
			    s_grc_param_defs[i].default_val[dev_data->chip_id];
}