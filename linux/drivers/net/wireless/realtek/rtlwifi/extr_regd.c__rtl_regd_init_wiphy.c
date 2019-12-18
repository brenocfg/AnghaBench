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
struct wiphy {void (* reg_notifier ) (struct wiphy*,struct regulatory_request*) ;int /*<<< orphan*/  regulatory_flags; } ;
struct rtl_regulatory {int dummy; } ;
struct ieee80211_regdomain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_REGDOM_SET_BY_DRIVER ; 
 int /*<<< orphan*/  REGULATORY_CUSTOM_REG ; 
 int /*<<< orphan*/  REGULATORY_DISABLE_BEACON_HINTS ; 
 int /*<<< orphan*/  REGULATORY_STRICT_REG ; 
 int /*<<< orphan*/  _rtl_reg_apply_radar_flags (struct wiphy*) ; 
 int /*<<< orphan*/  _rtl_reg_apply_world_flags (struct wiphy*,int /*<<< orphan*/ ,struct rtl_regulatory*) ; 
 struct ieee80211_regdomain* _rtl_regdomain_select (struct rtl_regulatory*) ; 
 int /*<<< orphan*/  wiphy_apply_custom_regulatory (struct wiphy*,struct ieee80211_regdomain const*) ; 

__attribute__((used)) static int _rtl_regd_init_wiphy(struct rtl_regulatory *reg,
				struct wiphy *wiphy,
				void (*reg_notifier)(struct wiphy *wiphy,
						     struct regulatory_request *
						     request))
{
	const struct ieee80211_regdomain *regd;

	wiphy->reg_notifier = reg_notifier;

	wiphy->regulatory_flags |= REGULATORY_CUSTOM_REG;
	wiphy->regulatory_flags &= ~REGULATORY_STRICT_REG;
	wiphy->regulatory_flags &= ~REGULATORY_DISABLE_BEACON_HINTS;
	regd = _rtl_regdomain_select(reg);
	wiphy_apply_custom_regulatory(wiphy, regd);
	_rtl_reg_apply_radar_flags(wiphy);
	_rtl_reg_apply_world_flags(wiphy, NL80211_REGDOM_SET_BY_DRIVER, reg);
	return 0;
}