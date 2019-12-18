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
struct rtl_regulatory {int dummy; } ;
struct regulatory_request {int initiator; } ;

/* Variables and functions */
#define  NL80211_REGDOM_SET_BY_CORE 131 
#define  NL80211_REGDOM_SET_BY_COUNTRY_IE 130 
#define  NL80211_REGDOM_SET_BY_DRIVER 129 
#define  NL80211_REGDOM_SET_BY_USER 128 
 int /*<<< orphan*/  _rtl_reg_apply_radar_flags (struct wiphy*) ; 
 int /*<<< orphan*/  _rtl_reg_apply_world_flags (struct wiphy*,int,struct rtl_regulatory*) ; 

__attribute__((used)) static int _rtl_reg_notifier_apply(struct wiphy *wiphy,
				   struct regulatory_request *request,
				   struct rtl_regulatory *reg)
{
	/* We always apply this */
	_rtl_reg_apply_radar_flags(wiphy);

	switch (request->initiator) {
	case NL80211_REGDOM_SET_BY_DRIVER:
	case NL80211_REGDOM_SET_BY_CORE:
	case NL80211_REGDOM_SET_BY_USER:
		break;
	case NL80211_REGDOM_SET_BY_COUNTRY_IE:
		_rtl_reg_apply_world_flags(wiphy, request->initiator, reg);
		break;
	}

	return 0;
}