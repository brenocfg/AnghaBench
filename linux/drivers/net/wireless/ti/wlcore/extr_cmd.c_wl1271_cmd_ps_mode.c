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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271_cmd_ps_params {int /*<<< orphan*/  auto_ps_timeout; int /*<<< orphan*/  ps_mode; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_PS_MODE ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl1271_cmd_ps_params*) ; 
 struct wl1271_cmd_ps_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_cmd_ps_params*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wl1271_cmd_ps_mode(struct wl1271 *wl, struct wl12xx_vif *wlvif,
		       u8 ps_mode, u16 auto_ps_timeout)
{
	struct wl1271_cmd_ps_params *ps_params = NULL;
	int ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd set ps mode");

	ps_params = kzalloc(sizeof(*ps_params), GFP_KERNEL);
	if (!ps_params) {
		ret = -ENOMEM;
		goto out;
	}

	ps_params->role_id = wlvif->role_id;
	ps_params->ps_mode = ps_mode;
	ps_params->auto_ps_timeout = auto_ps_timeout;

	ret = wl1271_cmd_send(wl, CMD_SET_PS_MODE, ps_params,
			      sizeof(*ps_params), 0);
	if (ret < 0) {
		wl1271_error("cmd set_ps_mode failed");
		goto out;
	}

out:
	kfree(ps_params);
	return ret;
}