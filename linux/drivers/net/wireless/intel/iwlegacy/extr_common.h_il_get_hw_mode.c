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
struct il_priv {TYPE_2__* hw; } ;
struct ieee80211_supported_band {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_4__ {TYPE_1__* wiphy; } ;
struct TYPE_3__ {struct ieee80211_supported_band const** bands; } ;

/* Variables and functions */

__attribute__((used)) static inline const struct ieee80211_supported_band *
il_get_hw_mode(struct il_priv *il, enum nl80211_band band)
{
	return il->hw->wiphy->bands[band];
}