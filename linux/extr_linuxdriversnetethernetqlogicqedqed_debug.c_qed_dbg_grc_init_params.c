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
struct TYPE_2__ {int params_initialized; } ;
struct dbg_tools_data {TYPE_1__ grc; } ;
struct qed_hwfn {struct dbg_tools_data dbg_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_dbg_grc_set_params_default (struct qed_hwfn*) ; 

__attribute__((used)) static void qed_dbg_grc_init_params(struct qed_hwfn *p_hwfn)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;

	if (!dev_data->grc.params_initialized) {
		qed_dbg_grc_set_params_default(p_hwfn);
		dev_data->grc.params_initialized = 1;
	}
}