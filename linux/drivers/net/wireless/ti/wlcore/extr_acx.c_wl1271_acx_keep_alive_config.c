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
typedef  void* u8 ;
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271_acx_keep_alive_config {int /*<<< orphan*/  trigger; void* tpl_validation; void* index; int /*<<< orphan*/  period; int /*<<< orphan*/  role_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  keep_alive_interval; } ;
struct TYPE_4__ {TYPE_1__ conn; } ;
struct wl1271 {TYPE_2__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_KEEP_ALIVE_NO_TX ; 
 int /*<<< orphan*/  ACX_SET_KEEP_ALIVE_CONFIG ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl1271_acx_keep_alive_config*) ; 
 struct wl1271_acx_keep_alive_config* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_acx_keep_alive_config*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_keep_alive_config(struct wl1271 *wl, struct wl12xx_vif *wlvif,
				 u8 index, u8 tpl_valid)
{
	struct wl1271_acx_keep_alive_config *acx = NULL;
	int ret = 0;

	wl1271_debug(DEBUG_ACX, "acx keep alive config");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->role_id = wlvif->role_id;
	acx->period = cpu_to_le32(wl->conf.conn.keep_alive_interval);
	acx->index = index;
	acx->tpl_validation = tpl_valid;
	acx->trigger = ACX_KEEP_ALIVE_NO_TX;

	ret = wl1271_cmd_configure(wl, ACX_SET_KEEP_ALIVE_CONFIG,
				   acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("acx keep alive config failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}