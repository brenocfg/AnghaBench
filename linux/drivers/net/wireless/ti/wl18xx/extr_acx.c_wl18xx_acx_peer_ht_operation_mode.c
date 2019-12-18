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
struct wlcore_peer_ht_operation_mode {int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  hlid; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_PEER_HT_OPERATION_MODE_CFG ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WLCORE_BANDWIDTH_20MHZ ; 
 int /*<<< orphan*/  WLCORE_BANDWIDTH_40MHZ ; 
 int /*<<< orphan*/  kfree (struct wlcore_peer_ht_operation_mode*) ; 
 struct wlcore_peer_ht_operation_mode* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wlcore_peer_ht_operation_mode*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl18xx_acx_peer_ht_operation_mode(struct wl1271 *wl, u8 hlid, bool wide)
{
	struct wlcore_peer_ht_operation_mode *acx;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx peer ht operation mode hlid %d bw %d",
		     hlid, wide);

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->hlid = hlid;
	acx->bandwidth = wide ? WLCORE_BANDWIDTH_40MHZ : WLCORE_BANDWIDTH_20MHZ;

	ret = wl1271_cmd_configure(wl, ACX_PEER_HT_OPERATION_MODE_CFG, acx,
				   sizeof(*acx));

	if (ret < 0) {
		wl1271_warning("acx peer ht operation mode failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;

}