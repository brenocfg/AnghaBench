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
struct ieee80211_supported_band {struct ieee80211_channel* channels; int /*<<< orphan*/  n_channels; } ;
struct ieee80211_channel {int dummy; } ;
struct ath_softc {struct ath_chanctx* chanctx; int /*<<< orphan*/  sc_ah; } ;
struct ath_common {struct ieee80211_supported_band* sbands; } ;
struct ath_chanctx {int flush_timeout; TYPE_1__* acq; int /*<<< orphan*/  txpower; int /*<<< orphan*/  vifs; int /*<<< orphan*/  chandef; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  acq_old; int /*<<< orphan*/  acq_new; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ATH9K_NUM_CHANCTX ; 
 int /*<<< orphan*/  ATH_TXPOWER_MAX ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  NL80211_CHAN_HT20 ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_chandef_create (int /*<<< orphan*/ *,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void ath_chanctx_init(struct ath_softc *sc)
{
	struct ath_chanctx *ctx;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ieee80211_supported_band *sband;
	struct ieee80211_channel *chan;
	int i, j;

	sband = &common->sbands[NL80211_BAND_2GHZ];
	if (!sband->n_channels)
		sband = &common->sbands[NL80211_BAND_5GHZ];

	chan = &sband->channels[0];
	for (i = 0; i < ATH9K_NUM_CHANCTX; i++) {
		ctx = &sc->chanctx[i];
		cfg80211_chandef_create(&ctx->chandef, chan, NL80211_CHAN_HT20);
		INIT_LIST_HEAD(&ctx->vifs);
		ctx->txpower = ATH_TXPOWER_MAX;
		ctx->flush_timeout = HZ / 5; /* 200ms */
		for (j = 0; j < ARRAY_SIZE(ctx->acq); j++) {
			INIT_LIST_HEAD(&ctx->acq[j].acq_new);
			INIT_LIST_HEAD(&ctx->acq[j].acq_old);
			spin_lock_init(&ctx->acq[j].lock);
		}
	}
}