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
typedef  scalar_t__ u64 ;
struct wl1251_filter_params {int enabled; int /*<<< orphan*/  mc_list_length; int /*<<< orphan*/ * mc_list; } ;
struct wl1251 {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  rx_filter; int /*<<< orphan*/  rx_config; int /*<<< orphan*/  bssid; } ;
struct ieee80211_hw {struct wl1251* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_BSSID_FILTER_EN ; 
 int /*<<< orphan*/  CFG_MC_FILTER_EN ; 
 int /*<<< orphan*/  CFG_RX_CTL_EN ; 
 int /*<<< orphan*/  CFG_RX_FCS_ERROR ; 
 int /*<<< orphan*/  CFG_RX_PREQ_EN ; 
 int /*<<< orphan*/  CFG_SSID_FILTER_EN ; 
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 unsigned int FIF_ALLMULTI ; 
 unsigned int FIF_BCN_PRBRESP_PROMISC ; 
 unsigned int FIF_CONTROL ; 
 unsigned int FIF_FCSFAIL ; 
 unsigned int FIF_OTHER_BSS ; 
 unsigned int FIF_PROBE_REQ ; 
 int /*<<< orphan*/  WL1251_DEFAULT_RX_CONFIG ; 
 int /*<<< orphan*/  WL1251_DEFAULT_RX_FILTER ; 
 scalar_t__ WL1251_STATE_OFF ; 
 unsigned int WL1251_SUPPORTED_FILTERS ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl1251_filter_params*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wl1251_acx_group_address_tbl (struct wl1251*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_acx_rx_config (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_ps_elp_sleep (struct wl1251*) ; 
 int wl1251_ps_elp_wakeup (struct wl1251*) ; 

__attribute__((used)) static void wl1251_op_configure_filter(struct ieee80211_hw *hw,
				       unsigned int changed,
				       unsigned int *total, u64 multicast)
{
	struct wl1251_filter_params *fp = (void *)(unsigned long)multicast;
	struct wl1251 *wl = hw->priv;
	int ret;

	wl1251_debug(DEBUG_MAC80211, "mac80211 configure filter");

	*total &= WL1251_SUPPORTED_FILTERS;
	changed &= WL1251_SUPPORTED_FILTERS;

	if (changed == 0) {
		/* no filters which we support changed */
		kfree(fp);
		return;
	}

	mutex_lock(&wl->mutex);

	wl->rx_config = WL1251_DEFAULT_RX_CONFIG;
	wl->rx_filter = WL1251_DEFAULT_RX_FILTER;

	if (*total & FIF_ALLMULTI)
		/*
		 * CFG_MC_FILTER_EN in rx_config needs to be 0 to receive
		 * all multicast frames
		 */
		wl->rx_config &= ~CFG_MC_FILTER_EN;
	if (*total & FIF_FCSFAIL)
		wl->rx_filter |= CFG_RX_FCS_ERROR;
	if (*total & FIF_BCN_PRBRESP_PROMISC) {
		wl->rx_config &= ~CFG_BSSID_FILTER_EN;
		wl->rx_config &= ~CFG_SSID_FILTER_EN;
	}
	if (*total & FIF_CONTROL)
		wl->rx_filter |= CFG_RX_CTL_EN;
	if (*total & FIF_OTHER_BSS || is_zero_ether_addr(wl->bssid))
		wl->rx_config &= ~CFG_BSSID_FILTER_EN;
	if (*total & FIF_PROBE_REQ)
		wl->rx_filter |= CFG_RX_PREQ_EN;

	if (wl->state == WL1251_STATE_OFF)
		goto out;

	ret = wl1251_ps_elp_wakeup(wl);
	if (ret < 0)
		goto out;

	if (*total & FIF_ALLMULTI)
		ret = wl1251_acx_group_address_tbl(wl, false, NULL, 0);
	else if (fp)
		ret = wl1251_acx_group_address_tbl(wl, fp->enabled,
						   fp->mc_list,
						   fp->mc_list_length);
	if (ret < 0)
		goto out;

	/* send filters to firmware */
	wl1251_acx_rx_config(wl, wl->rx_config, wl->rx_filter);

	wl1251_ps_elp_sleep(wl);

out:
	mutex_unlock(&wl->mutex);
	kfree(fp);
}