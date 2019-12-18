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
struct conf_ap_sleep_settings {int /*<<< orphan*/  idle_conn_thresh; int /*<<< orphan*/  max_stations_thresh; int /*<<< orphan*/  connected_duty_cycle; int /*<<< orphan*/  idle_duty_cycle; } ;
struct TYPE_2__ {struct conf_ap_sleep_settings ap_sleep; } ;
struct wl18xx_priv {TYPE_1__ conf; } ;
struct wl1271 {struct wl18xx_priv* priv; } ;
struct acx_ap_sleep_cfg {int /*<<< orphan*/  idle_conn_thresh; int /*<<< orphan*/  max_stations_thresh; int /*<<< orphan*/  connected_duty_cycle; int /*<<< orphan*/  idle_duty_cycle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_AP_SLEEP_CFG ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_ap_sleep_cfg*) ; 
 struct acx_ap_sleep_cfg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct acx_ap_sleep_cfg*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl18xx_acx_ap_sleep(struct wl1271 *wl)
{
	struct wl18xx_priv *priv = wl->priv;
	struct acx_ap_sleep_cfg *acx;
	struct conf_ap_sleep_settings *conf = &priv->conf.ap_sleep;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx config ap sleep");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->idle_duty_cycle = conf->idle_duty_cycle;
	acx->connected_duty_cycle = conf->connected_duty_cycle;
	acx->max_stations_thresh = conf->max_stations_thresh;
	acx->idle_conn_thresh = conf->idle_conn_thresh;

	ret = wl1271_cmd_configure(wl, ACX_AP_SLEEP_CFG, acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("acx config ap-sleep failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}