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
struct wcn36xx_vif {int /*<<< orphan*/  pw_state; } ;
struct wcn36xx {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCN36XX_BMPS ; 
 int /*<<< orphan*/  WCN36XX_DBG_PMC ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcn36xx_err (char*) ; 
 int wcn36xx_smd_enter_bmps (struct wcn36xx*,struct ieee80211_vif*) ; 
 struct wcn36xx_vif* wcn36xx_vif_to_priv (struct ieee80211_vif*) ; 

int wcn36xx_pmc_enter_bmps_state(struct wcn36xx *wcn,
				 struct ieee80211_vif *vif)
{
	int ret = 0;
	struct wcn36xx_vif *vif_priv = wcn36xx_vif_to_priv(vif);
	/* TODO: Make sure the TX chain clean */
	ret = wcn36xx_smd_enter_bmps(wcn, vif);
	if (!ret) {
		wcn36xx_dbg(WCN36XX_DBG_PMC, "Entered BMPS\n");
		vif_priv->pw_state = WCN36XX_BMPS;
	} else {
		/*
		 * One of the reasons why HW will not enter BMPS is because
		 * driver is trying to enter bmps before first beacon was
		 * received just after auth complete
		 */
		wcn36xx_err("Can not enter BMPS!\n");
	}
	return ret;
}