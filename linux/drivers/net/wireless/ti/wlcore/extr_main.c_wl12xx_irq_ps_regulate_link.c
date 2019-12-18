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
typedef  scalar_t__ u8 ;
struct wl12xx_vif {int dummy; } ;
struct wl1271 {int active_link_count; int ap_count; int /*<<< orphan*/  ap_fw_ps_map; } ;

/* Variables and functions */
 scalar_t__ WL1271_PS_STA_MAX_PACKETS ; 
 int test_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl12xx_ps_link_end (struct wl1271*,struct wl12xx_vif*,scalar_t__) ; 
 int /*<<< orphan*/  wl12xx_ps_link_start (struct wl1271*,struct wl12xx_vif*,scalar_t__,int) ; 

__attribute__((used)) static void wl12xx_irq_ps_regulate_link(struct wl1271 *wl,
					struct wl12xx_vif *wlvif,
					u8 hlid, u8 tx_pkts)
{
	bool fw_ps;

	fw_ps = test_bit(hlid, &wl->ap_fw_ps_map);

	/*
	 * Wake up from high level PS if the STA is asleep with too little
	 * packets in FW or if the STA is awake.
	 */
	if (!fw_ps || tx_pkts < WL1271_PS_STA_MAX_PACKETS)
		wl12xx_ps_link_end(wl, wlvif, hlid);

	/*
	 * Start high-level PS if the STA is asleep with enough blocks in FW.
	 * Make an exception if this is the only connected link. In this
	 * case FW-memory congestion is less of a problem.
	 * Note that a single connected STA means 2*ap_count + 1 active links,
	 * since we must account for the global and broadcast AP links
	 * for each AP. The "fw_ps" check assures us the other link is a STA
	 * connected to the AP. Otherwise the FW would not set the PSM bit.
	 */
	else if (wl->active_link_count > (wl->ap_count*2 + 1) && fw_ps &&
		 tx_pkts >= WL1271_PS_STA_MAX_PACKETS)
		wl12xx_ps_link_start(wl, wlvif, hlid, true);
}