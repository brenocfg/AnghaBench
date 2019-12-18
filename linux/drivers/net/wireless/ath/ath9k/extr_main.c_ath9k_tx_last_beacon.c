#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  enable_beacon; } ;
struct ieee80211_vif {scalar_t__ drv_priv; TYPE_2__ bss_conf; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_vif {struct ath_buf* av_bcbuf; } ;
struct ath_tx_status {int ts_status; } ;
struct TYPE_6__ {int tx_processed; int tx_last; struct ieee80211_vif** bslot; } ;
struct ath_softc {TYPE_3__ beacon; int /*<<< orphan*/  bcon_tasklet; struct ath_hw* sc_ah; } ;
struct TYPE_4__ {int hw_caps; } ;
struct ath_hw {TYPE_1__ caps; } ;
struct ath_buf {int /*<<< orphan*/  bf_desc; int /*<<< orphan*/  bf_mpdu; } ;

/* Variables and functions */
 int ATH9K_HW_CAP_EDMA ; 
 int ATH9K_TXERR_MASK ; 
 int EINPROGRESS ; 
 int ath9k_hw_txprocdesc (struct ath_hw*,int /*<<< orphan*/ ,struct ath_tx_status*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_tx_last_beacon(struct ieee80211_hw *hw)
{
	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;
	struct ieee80211_vif *vif;
	struct ath_vif *avp;
	struct ath_buf *bf;
	struct ath_tx_status ts;
	bool edma = !!(ah->caps.hw_caps & ATH9K_HW_CAP_EDMA);
	int status;

	vif = sc->beacon.bslot[0];
	if (!vif)
		return 0;

	if (!vif->bss_conf.enable_beacon)
		return 0;

	avp = (void *)vif->drv_priv;

	if (!sc->beacon.tx_processed && !edma) {
		tasklet_disable(&sc->bcon_tasklet);

		bf = avp->av_bcbuf;
		if (!bf || !bf->bf_mpdu)
			goto skip;

		status = ath9k_hw_txprocdesc(ah, bf->bf_desc, &ts);
		if (status == -EINPROGRESS)
			goto skip;

		sc->beacon.tx_processed = true;
		sc->beacon.tx_last = !(ts.ts_status & ATH9K_TXERR_MASK);

skip:
		tasklet_enable(&sc->bcon_tasklet);
	}

	return sc->beacon.tx_last;
}