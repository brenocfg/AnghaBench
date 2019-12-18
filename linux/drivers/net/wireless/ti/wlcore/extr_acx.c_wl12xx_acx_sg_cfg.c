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
struct conf_sg_settings {int /*<<< orphan*/ * params; } ;
struct TYPE_2__ {struct conf_sg_settings sg; } ;
struct wl1271 {TYPE_1__ conf; } ;
struct acx_bt_wlan_coex_param {int /*<<< orphan*/  param_idx; int /*<<< orphan*/ * params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_SG_CFG ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WLCORE_CONF_SG_PARAMS_ALL ; 
 int WLCORE_CONF_SG_PARAMS_MAX ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acx_bt_wlan_coex_param*) ; 
 struct acx_bt_wlan_coex_param* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct acx_bt_wlan_coex_param*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl12xx_acx_sg_cfg(struct wl1271 *wl)
{
	struct acx_bt_wlan_coex_param *param;
	struct conf_sg_settings *c = &wl->conf.sg;
	int i, ret;

	wl1271_debug(DEBUG_ACX, "acx sg cfg");

	param = kzalloc(sizeof(*param), GFP_KERNEL);
	if (!param) {
		ret = -ENOMEM;
		goto out;
	}

	/* BT-WLAN coext parameters */
	for (i = 0; i < WLCORE_CONF_SG_PARAMS_MAX; i++)
		param->params[i] = cpu_to_le32(c->params[i]);
	param->param_idx = WLCORE_CONF_SG_PARAMS_ALL;

	ret = wl1271_cmd_configure(wl, ACX_SG_CFG, param, sizeof(*param));
	if (ret < 0) {
		wl1271_warning("failed to set sg config: %d", ret);
		goto out;
	}

out:
	kfree(param);
	return ret;
}