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
struct ieee80211_hw {TYPE_1__* wiphy; struct ath_softc* priv; } ;
struct ath_softc {int driver_data; int /*<<< orphan*/  dev; scalar_t__ force_wow; struct ath_hw* sc_ah; } ;
struct ath_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * wowlan; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9462_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565_11_OR_LATER (struct ath_hw*) ; 
 int ATH9K_PCI_WOW ; 
 int /*<<< orphan*/  ath9k_wowlan_support ; 
 int /*<<< orphan*/  ath9k_wowlan_support_legacy ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ ,int) ; 

void ath9k_init_wow(struct ieee80211_hw *hw)
{
	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;

	if ((sc->driver_data & ATH9K_PCI_WOW) || sc->force_wow) {
		if (AR_SREV_9462_20_OR_LATER(ah) || AR_SREV_9565_11_OR_LATER(ah))
			hw->wiphy->wowlan = &ath9k_wowlan_support;
		else
			hw->wiphy->wowlan = &ath9k_wowlan_support_legacy;

		device_init_wakeup(sc->dev, 1);
	}
}