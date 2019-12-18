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
typedef  int u32 ;
struct ieee80211_conf {int flags; int /*<<< orphan*/  chandef; } ;
struct ieee80211_hw {struct ieee80211_conf conf; struct ath_softc* priv; } ;
struct ath_softc {int ps_idle; int /*<<< orphan*/  mutex; struct ath_hw* sc_ah; int /*<<< orphan*/  sc_pm_lock; struct ath_chanctx* cur_chan; } ;
struct ath_hw {int is_monitoring; } ;
struct ath_common {int dummy; } ;
struct ath_chanctx {int offchannel; int /*<<< orphan*/  chandef; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int IEEE80211_CONF_CHANGE_CHANNEL ; 
 int IEEE80211_CONF_CHANGE_IDLE ; 
 int IEEE80211_CONF_CHANGE_MONITOR ; 
 int IEEE80211_CONF_CHANGE_PS ; 
 int IEEE80211_CONF_IDLE ; 
 int IEEE80211_CONF_MONITOR ; 
 int IEEE80211_CONF_OFFCHANNEL ; 
 int IEEE80211_CONF_PS ; 
 int /*<<< orphan*/  ath9k_disable_ps (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_enable_ps (struct ath_softc*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_is_chanctx_enabled () ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_start_btcoex (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_stop_btcoex (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_cancel_work (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_chanctx_set_channel (struct ath_softc*,struct ath_chanctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ath9k_config(struct ieee80211_hw *hw, u32 changed)
{
	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ieee80211_conf *conf = &hw->conf;
	struct ath_chanctx *ctx = sc->cur_chan;

	ath9k_ps_wakeup(sc);
	mutex_lock(&sc->mutex);

	if (changed & IEEE80211_CONF_CHANGE_IDLE) {
		sc->ps_idle = !!(conf->flags & IEEE80211_CONF_IDLE);
		if (sc->ps_idle) {
			ath_cancel_work(sc);
			ath9k_stop_btcoex(sc);
		} else {
			ath9k_start_btcoex(sc);
			/*
			 * The chip needs a reset to properly wake up from
			 * full sleep
			 */
			ath_chanctx_set_channel(sc, ctx, &ctx->chandef);
		}
	}

	/*
	 * We just prepare to enable PS. We have to wait until our AP has
	 * ACK'd our null data frame to disable RX otherwise we'll ignore
	 * those ACKs and end up retransmitting the same null data frames.
	 * IEEE80211_CONF_CHANGE_PS is only passed by mac80211 for STA mode.
	 */
	if (changed & IEEE80211_CONF_CHANGE_PS) {
		unsigned long flags;
		spin_lock_irqsave(&sc->sc_pm_lock, flags);
		if (conf->flags & IEEE80211_CONF_PS)
			ath9k_enable_ps(sc);
		else
			ath9k_disable_ps(sc);
		spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
	}

	if (changed & IEEE80211_CONF_CHANGE_MONITOR) {
		if (conf->flags & IEEE80211_CONF_MONITOR) {
			ath_dbg(common, CONFIG, "Monitor mode is enabled\n");
			sc->sc_ah->is_monitoring = true;
		} else {
			ath_dbg(common, CONFIG, "Monitor mode is disabled\n");
			sc->sc_ah->is_monitoring = false;
		}
	}

	if (!ath9k_is_chanctx_enabled() && (changed & IEEE80211_CONF_CHANGE_CHANNEL)) {
		ctx->offchannel = !!(conf->flags & IEEE80211_CONF_OFFCHANNEL);
		ath_chanctx_set_channel(sc, ctx, &hw->conf.chandef);
	}

	mutex_unlock(&sc->mutex);
	ath9k_ps_restore(sc);

	return 0;
}