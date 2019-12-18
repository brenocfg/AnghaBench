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
typedef  int u32 ;
struct wiphy {int /*<<< orphan*/  retry_short; } ;
struct wil6210_priv {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int WIPHY_PARAM_FRAG_THRESHOLD ; 
 int WIPHY_PARAM_RETRY_LONG ; 
 int WIPHY_PARAM_RETRY_SHORT ; 
 int WIPHY_PARAM_RTS_THRESHOLD ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 
 int wmi_set_mgmt_retry (struct wil6210_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wil_cfg80211_set_wiphy_params(struct wiphy *wiphy, u32 changed)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	int rc;

	/* these parameters are explicitly not supported */
	if (changed & (WIPHY_PARAM_RETRY_LONG |
		       WIPHY_PARAM_FRAG_THRESHOLD |
		       WIPHY_PARAM_RTS_THRESHOLD))
		return -ENOTSUPP;

	if (changed & WIPHY_PARAM_RETRY_SHORT) {
		rc = wmi_set_mgmt_retry(wil, wiphy->retry_short);
		if (rc)
			return rc;
	}

	return 0;
}