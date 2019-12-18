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
struct wiphy {int /*<<< orphan*/ * bands; } ;
struct regulatory_request {int /*<<< orphan*/ * alpha2; int /*<<< orphan*/  initiator; } ;
struct qtnf_wmac {int /*<<< orphan*/  macid; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int NUM_NL80211_BANDS ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,...) ; 
 int qtnf_cmd_band_info_get (struct qtnf_wmac*,int /*<<< orphan*/ ) ; 
 int qtnf_cmd_reg_notify (struct qtnf_wmac*,struct regulatory_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_mac_slave_radar_get (struct wiphy*) ; 
 struct qtnf_wmac* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static void qtnf_cfg80211_reg_notifier(struct wiphy *wiphy,
				       struct regulatory_request *req)
{
	struct qtnf_wmac *mac = wiphy_priv(wiphy);
	enum nl80211_band band;
	int ret;

	pr_debug("MAC%u: initiator=%d alpha=%c%c\n", mac->macid, req->initiator,
		 req->alpha2[0], req->alpha2[1]);

	ret = qtnf_cmd_reg_notify(mac, req, qtnf_mac_slave_radar_get(wiphy));
	if (ret) {
		pr_err("MAC%u: failed to update region to %c%c: %d\n",
		       mac->macid, req->alpha2[0], req->alpha2[1], ret);
		return;
	}

	for (band = 0; band < NUM_NL80211_BANDS; ++band) {
		if (!wiphy->bands[band])
			continue;

		ret = qtnf_cmd_band_info_get(mac, wiphy->bands[band]);
		if (ret)
			pr_err("MAC%u: failed to update band %u\n",
			       mac->macid, band);
	}
}