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
struct wl1251 {int /*<<< orphan*/  rx_config; int /*<<< orphan*/  bssid; int /*<<< orphan*/  tx_mgmt_frm_mod; int /*<<< orphan*/  tx_mgmt_frm_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_BSSID_FILTER_EN ; 
 int /*<<< orphan*/  DEFAULT_HW_GEN_MODULATION_TYPE ; 
 int /*<<< orphan*/  DEFAULT_HW_GEN_TX_RATE ; 
 int /*<<< orphan*/  JOIN_EVENT_COMPLETE_ID ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int wl1251_acx_frame_rates (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_join (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1251_event_wait (struct wl1251*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wl1251_warning (char*) ; 

__attribute__((used)) static int wl1251_join(struct wl1251 *wl, u8 bss_type, u8 channel,
		       u16 beacon_interval, u8 dtim_period)
{
	int ret;

	ret = wl1251_acx_frame_rates(wl, DEFAULT_HW_GEN_TX_RATE,
				     DEFAULT_HW_GEN_MODULATION_TYPE,
				     wl->tx_mgmt_frm_rate,
				     wl->tx_mgmt_frm_mod);
	if (ret < 0)
		goto out;

	/*
	 * Join command applies filters, and if we are not associated,
	 * BSSID filter must be disabled for association to work.
	 */
	if (is_zero_ether_addr(wl->bssid))
		wl->rx_config &= ~CFG_BSSID_FILTER_EN;

	ret = wl1251_cmd_join(wl, bss_type, channel, beacon_interval,
			      dtim_period);
	if (ret < 0)
		goto out;

	ret = wl1251_event_wait(wl, JOIN_EVENT_COMPLETE_ID, 100);
	if (ret < 0)
		wl1251_warning("join timeout");

out:
	return ret;
}