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
struct regulatory_request {int initiator; int /*<<< orphan*/ * alpha2; } ;
struct mwifiex_private {int dummy; } ;
struct mwifiex_adapter {char* country_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  MWIFIEX_BSS_ROLE_ANY ; 
#define  NL80211_REGDOM_SET_BY_CORE 131 
#define  NL80211_REGDOM_SET_BY_COUNTRY_IE 130 
#define  NL80211_REGDOM_SET_BY_DRIVER 129 
#define  NL80211_REGDOM_SET_BY_USER 128 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 struct mwifiex_adapter* mwifiex_cfg80211_get_adapter (struct wiphy*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mwifiex_dnld_txpwr_table (struct mwifiex_private*) ; 
 struct mwifiex_private* mwifiex_get_priv (struct mwifiex_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_reg_apply_radar_flags (struct wiphy*) ; 
 int /*<<< orphan*/  mwifiex_send_domain_info_cmd_fw (struct wiphy*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void mwifiex_reg_notifier(struct wiphy *wiphy,
				 struct regulatory_request *request)
{
	struct mwifiex_adapter *adapter = mwifiex_cfg80211_get_adapter(wiphy);
	struct mwifiex_private *priv = mwifiex_get_priv(adapter,
							MWIFIEX_BSS_ROLE_ANY);
	mwifiex_dbg(adapter, INFO,
		    "info: cfg80211 regulatory domain callback for %c%c\n",
		    request->alpha2[0], request->alpha2[1]);
	mwifiex_reg_apply_radar_flags(wiphy);

	switch (request->initiator) {
	case NL80211_REGDOM_SET_BY_DRIVER:
	case NL80211_REGDOM_SET_BY_CORE:
	case NL80211_REGDOM_SET_BY_USER:
	case NL80211_REGDOM_SET_BY_COUNTRY_IE:
		break;
	default:
		mwifiex_dbg(adapter, ERROR,
			    "unknown regdom initiator: %d\n",
			    request->initiator);
		return;
	}

	/* Don't send world or same regdom info to firmware */
	if (strncmp(request->alpha2, "00", 2) &&
	    strncmp(request->alpha2, adapter->country_code,
		    sizeof(request->alpha2))) {
		memcpy(adapter->country_code, request->alpha2,
		       sizeof(request->alpha2));
		mwifiex_send_domain_info_cmd_fw(wiphy);
		mwifiex_dnld_txpwr_table(priv);
	}
}