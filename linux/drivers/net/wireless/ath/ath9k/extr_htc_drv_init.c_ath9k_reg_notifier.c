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
struct wiphy {int dummy; } ;
struct regulatory_request {int dummy; } ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_hw_regulatory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_reg_notifier_apply (struct wiphy*,struct regulatory_request*,int /*<<< orphan*/ ) ; 
 struct ieee80211_hw* wiphy_to_ieee80211_hw (struct wiphy*) ; 

__attribute__((used)) static void ath9k_reg_notifier(struct wiphy *wiphy,
			       struct regulatory_request *request)
{
	struct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	struct ath9k_htc_priv *priv = hw->priv;

	ath_reg_notifier_apply(wiphy, request,
			       ath9k_hw_regulatory(priv->ah));
}