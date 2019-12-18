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
typedef  int /*<<< orphan*/  u32 ;
struct wlcore_acx_peer_cap {void* supported_rates; void* ht_capabilites; int /*<<< orphan*/  hlid; int /*<<< orphan*/  ampdu_min_spacing; int /*<<< orphan*/  ampdu_max_length; } ;
struct wl1271 {int dummy; } ;
struct ieee80211_sta_ht_cap {int /*<<< orphan*/  ampdu_density; int /*<<< orphan*/  ampdu_factor; int /*<<< orphan*/  cap; scalar_t__ ht_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_PEER_CAP ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WL12XX_HT_CAP_HT_OPERATION ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wlcore_acx_peer_cap*) ; 
 struct wlcore_acx_peer_cap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wlcore_acx_peer_cap*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl18xx_acx_set_peer_cap(struct wl1271 *wl,
			    struct ieee80211_sta_ht_cap *ht_cap,
			    bool allow_ht_operation,
			    u32 rate_set, u8 hlid)
{
	struct wlcore_acx_peer_cap *acx;
	int ret = 0;
	u32 ht_capabilites = 0;

	wl1271_debug(DEBUG_ACX,
		     "acx set cap ht_supp: %d ht_cap: %d rates: 0x%x",
		     ht_cap->ht_supported, ht_cap->cap, rate_set);

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	if (allow_ht_operation && ht_cap->ht_supported) {
		/* no need to translate capabilities - use the spec values */
		ht_capabilites = ht_cap->cap;

		/*
		 * this bit is not employed by the spec but only by FW to
		 * indicate peer HT support
		 */
		ht_capabilites |= WL12XX_HT_CAP_HT_OPERATION;

		/* get data from A-MPDU parameters field */
		acx->ampdu_max_length = ht_cap->ampdu_factor;
		acx->ampdu_min_spacing = ht_cap->ampdu_density;
	}

	acx->hlid = hlid;
	acx->ht_capabilites = cpu_to_le32(ht_capabilites);
	acx->supported_rates = cpu_to_le32(rate_set);

	ret = wl1271_cmd_configure(wl, ACX_PEER_CAP, acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("acx ht capabilities setting failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}