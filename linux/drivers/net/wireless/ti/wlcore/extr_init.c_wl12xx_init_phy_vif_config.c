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
struct wl12xx_vif {int dummy; } ;
struct wl1271 {TYPE_2__* hw; } ;
struct TYPE_4__ {TYPE_1__* wiphy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rts_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SLOT_TIME ; 
 int wl1271_acx_rts_threshold (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ) ; 
 int wl1271_acx_service_period_timeout (struct wl1271*,struct wl12xx_vif*) ; 
 int wl1271_acx_slot (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl12xx_init_phy_vif_config(struct wl1271 *wl,
					    struct wl12xx_vif *wlvif)
{
	int ret;

	ret = wl1271_acx_slot(wl, wlvif, DEFAULT_SLOT_TIME);
	if (ret < 0)
		return ret;

	ret = wl1271_acx_service_period_timeout(wl, wlvif);
	if (ret < 0)
		return ret;

	ret = wl1271_acx_rts_threshold(wl, wlvif, wl->hw->wiphy->rts_threshold);
	if (ret < 0)
		return ret;

	return 0;
}