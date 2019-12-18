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
struct ieee80211_bss_conf {int beacon_int; int dtim_period; int /*<<< orphan*/  ibss_creator; int /*<<< orphan*/  bssid; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int dummy; } ;
struct ath_beacon_config {int beacon_interval; int dtim_period; int dtim_count; int bmiss_timeout; int /*<<< orphan*/  ibss_creator; } ;
struct ath_chanctx {struct ath_beacon_config beacon; } ;

/* Variables and functions */
 int ATH_DEFAULT_BMISS_LIMIT ; 
 int /*<<< orphan*/  BEACON ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_set_tsfadjust (struct ath_softc*,struct ath_beacon_config*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_cache_beacon_config(struct ath_softc *sc,
				      struct ath_chanctx *ctx,
				      struct ieee80211_bss_conf *bss_conf)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_beacon_config *cur_conf = &ctx->beacon;

	ath_dbg(common, BEACON,
		"Caching beacon data for BSS: %pM\n", bss_conf->bssid);

	cur_conf->beacon_interval = bss_conf->beacon_int;
	cur_conf->dtim_period = bss_conf->dtim_period;
	cur_conf->dtim_count = 1;
	cur_conf->ibss_creator = bss_conf->ibss_creator;

	/*
	 * It looks like mac80211 may end up using beacon interval of zero in
	 * some cases (at least for mesh point). Avoid getting into an
	 * infinite loop by using a bit safer value instead. To be safe,
	 * do sanity check on beacon interval for all operating modes.
	 */
	if (cur_conf->beacon_interval == 0)
		cur_conf->beacon_interval = 100;

	cur_conf->bmiss_timeout =
		ATH_DEFAULT_BMISS_LIMIT * cur_conf->beacon_interval;

	/*
	 * We don't parse dtim period from mac80211 during the driver
	 * initialization as it breaks association with hidden-ssid
	 * AP and it causes latency in roaming
	 */
	if (cur_conf->dtim_period == 0)
		cur_conf->dtim_period = 1;

	ath9k_set_tsfadjust(sc, cur_conf);
}