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
struct wcn36xx_vif {int /*<<< orphan*/  list; } ;
struct wcn36xx {int /*<<< orphan*/  conf_mutex; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCN36XX_DBG_MAC ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  wcn36xx_smd_delete_sta_self (struct wcn36xx*,int /*<<< orphan*/ ) ; 
 struct wcn36xx_vif* wcn36xx_vif_to_priv (struct ieee80211_vif*) ; 

__attribute__((used)) static void wcn36xx_remove_interface(struct ieee80211_hw *hw,
				     struct ieee80211_vif *vif)
{
	struct wcn36xx *wcn = hw->priv;
	struct wcn36xx_vif *vif_priv = wcn36xx_vif_to_priv(vif);
	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac remove interface vif %p\n", vif);

	mutex_lock(&wcn->conf_mutex);

	list_del(&vif_priv->list);
	wcn36xx_smd_delete_sta_self(wcn, vif->addr);

	mutex_unlock(&wcn->conf_mutex);
}