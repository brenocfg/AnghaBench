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
struct wl1271 {int /*<<< orphan*/  dynamic_fw_traces; } ;
struct acx_dynamic_fw_traces_cfg {int /*<<< orphan*/  dynamic_fw_traces; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_DYNAMIC_TRACES_CFG ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acx_dynamic_fw_traces_cfg*) ; 
 struct acx_dynamic_fw_traces_cfg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct acx_dynamic_fw_traces_cfg*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl18xx_acx_dynamic_fw_traces(struct wl1271 *wl)
{
	struct acx_dynamic_fw_traces_cfg *acx;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx dynamic fw traces config %d",
		     wl->dynamic_fw_traces);

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->dynamic_fw_traces = cpu_to_le32(wl->dynamic_fw_traces);

	ret = wl1271_cmd_configure(wl, ACX_DYNAMIC_TRACES_CFG,
				   acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("acx config dynamic fw traces failed: %d", ret);
		goto out;
	}
out:
	kfree(acx);
	return ret;
}