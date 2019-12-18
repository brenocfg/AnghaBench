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
struct iwl_priv {TYPE_2__* lib; } ;
struct TYPE_4__ {scalar_t__ temp_offset_v2; scalar_t__ need_temp_offset_calib; TYPE_1__* bt_params; } ;
struct TYPE_3__ {scalar_t__ advanced_bt_coexist; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_COEX_PRIO_TBL_EVT_INIT_CALIB2 ; 
 int /*<<< orphan*/  IWL_BT_COEX_ENV_OPEN ; 
 int iwl_send_bt_env (struct iwl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_send_calib_cfg (struct iwl_priv*) ; 
 int iwl_set_temperature_offset_calib (struct iwl_priv*) ; 
 int iwl_set_temperature_offset_calib_v2 (struct iwl_priv*) ; 

int iwl_init_alive_start(struct iwl_priv *priv)
{
	int ret;

	if (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist) {
		/*
		 * Tell uCode we are ready to perform calibration
		 * need to perform this before any calibration
		 * no need to close the envlope since we are going
		 * to load the runtime uCode later.
		 */
		ret = iwl_send_bt_env(priv, IWL_BT_COEX_ENV_OPEN,
			BT_COEX_PRIO_TBL_EVT_INIT_CALIB2);
		if (ret)
			return ret;

	}

	ret = iwl_send_calib_cfg(priv);
	if (ret)
		return ret;

	/**
	 * temperature offset calibration is only needed for runtime ucode,
	 * so prepare the value now.
	 */
	if (priv->lib->need_temp_offset_calib) {
		if (priv->lib->temp_offset_v2)
			return iwl_set_temperature_offset_calib_v2(priv);
		else
			return iwl_set_temperature_offset_calib(priv);
	}

	return 0;
}