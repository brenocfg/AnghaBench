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
struct wl18xx_acx_checksum_state {int /*<<< orphan*/  checksum_state; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_CSUM_CONFIG ; 
 int /*<<< orphan*/  CHECKSUM_OFFLOAD_ENABLED ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl18xx_acx_checksum_state*) ; 
 struct wl18xx_acx_checksum_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wl18xx_acx_checksum_state*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl18xx_acx_set_checksum_state(struct wl1271 *wl)
{
	struct wl18xx_acx_checksum_state *acx;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx checksum state");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->checksum_state = CHECKSUM_OFFLOAD_ENABLED;

	ret = wl1271_cmd_configure(wl, ACX_CSUM_CONFIG, acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("failed to set Tx checksum state: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}