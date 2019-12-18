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
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */
 int ath9k_has_tx_pending (struct ath_softc*,int) ; 

__attribute__((used)) static bool ath9k_tx_frames_pending(struct ieee80211_hw *hw)
{
	struct ath_softc *sc = hw->priv;

	return ath9k_has_tx_pending(sc, true);
}