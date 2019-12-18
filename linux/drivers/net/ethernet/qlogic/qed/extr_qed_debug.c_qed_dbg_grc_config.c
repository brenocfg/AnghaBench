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
struct qed_hwfn {int dummy; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
typedef  enum dbg_grc_params { ____Placeholder_dbg_grc_params } dbg_grc_params ;
struct TYPE_2__ {int /*<<< orphan*/  crash_preset_val; int /*<<< orphan*/  exclude_all_preset_val; scalar_t__ is_persistent; scalar_t__ is_preset; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int DBG_GRC_PARAM_CRASH ; 
 int DBG_GRC_PARAM_EXCLUDE_ALL ; 
 int DBG_STATUS_INVALID_ARGS ; 
 int DBG_STATUS_OK ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int MAX_DBG_GRC_PARAMS ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 int qed_dbg_dev_init (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_dbg_grc_init_params (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_grc_set_param (struct qed_hwfn*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* s_grc_param_defs ; 

enum dbg_status qed_dbg_grc_config(struct qed_hwfn *p_hwfn,
				   struct qed_ptt *p_ptt,
				   enum dbg_grc_params grc_param, u32 val)
{
	enum dbg_status status;
	int i;

	DP_VERBOSE(p_hwfn, QED_MSG_DEBUG,
		   "dbg_grc_config: paramId = %d, val = %d\n", grc_param, val);

	status = qed_dbg_dev_init(p_hwfn, p_ptt);
	if (status != DBG_STATUS_OK)
		return status;

	/* Initializes the GRC parameters (if not initialized). Needed in order
	 * to set the default parameter values for the first time.
	 */
	qed_dbg_grc_init_params(p_hwfn);

	if (grc_param >= MAX_DBG_GRC_PARAMS)
		return DBG_STATUS_INVALID_ARGS;
	if (val < s_grc_param_defs[grc_param].min ||
	    val > s_grc_param_defs[grc_param].max)
		return DBG_STATUS_INVALID_ARGS;

	if (s_grc_param_defs[grc_param].is_preset) {
		/* Preset param */

		/* Disabling a preset is not allowed. Call
		 * dbg_grc_set_params_default instead.
		 */
		if (!val)
			return DBG_STATUS_INVALID_ARGS;

		/* Update all params with the preset values */
		for (i = 0; i < MAX_DBG_GRC_PARAMS; i++) {
			u32 preset_val;

			/* Skip persistent params */
			if (s_grc_param_defs[i].is_persistent)
				continue;

			/* Find preset value */
			if (grc_param == DBG_GRC_PARAM_EXCLUDE_ALL)
				preset_val =
				    s_grc_param_defs[i].exclude_all_preset_val;
			else if (grc_param == DBG_GRC_PARAM_CRASH)
				preset_val =
				    s_grc_param_defs[i].crash_preset_val;
			else
				return DBG_STATUS_INVALID_ARGS;

			qed_grc_set_param(p_hwfn,
					  (enum dbg_grc_params)i, preset_val);
		}
	} else {
		/* Regular param - set its value */
		qed_grc_set_param(p_hwfn, grc_param, val);
	}

	return DBG_STATUS_OK;
}