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
struct TYPE_2__ {int /*<<< orphan*/  hlid; } ;
struct wl12xx_vif {scalar_t__ bss_type; TYPE_1__ sta; int /*<<< orphan*/  flags; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WLVIF_FLAG_STA_ASSOCIATED ; 
 int /*<<< orphan*/  WLVIF_FLAG_STA_STATE_SENT ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_info (char*) ; 
 int wl12xx_cmd_set_peer_state (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl12xx_set_authorized(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int ret;

	if (WARN_ON(wlvif->bss_type != BSS_TYPE_STA_BSS))
		return -EINVAL;

	if (!test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvif->flags))
		return 0;

	if (test_and_set_bit(WLVIF_FLAG_STA_STATE_SENT, &wlvif->flags))
		return 0;

	ret = wl12xx_cmd_set_peer_state(wl, wlvif, wlvif->sta.hlid);
	if (ret < 0)
		return ret;

	wl1271_info("Association completed.");
	return 0;
}