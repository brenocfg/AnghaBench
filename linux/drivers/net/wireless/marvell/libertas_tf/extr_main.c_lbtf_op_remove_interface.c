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
struct lbtf_private {TYPE_1__* vif; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct lbtf_private* priv; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBTF_DEB_MACOPS ; 
 int /*<<< orphan*/  LBTF_PASSIVE_MODE ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  lbtf_beacon_ctrl (struct lbtf_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_set_bssid (struct lbtf_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbtf_set_mode (struct lbtf_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lbtf_op_remove_interface(struct ieee80211_hw *hw,
			struct ieee80211_vif *vif)
{
	struct lbtf_private *priv = hw->priv;
	lbtf_deb_enter(LBTF_DEB_MACOPS);

	if (priv->vif->type == NL80211_IFTYPE_AP ||
	    priv->vif->type == NL80211_IFTYPE_MESH_POINT)
		lbtf_beacon_ctrl(priv, 0, 0);
	lbtf_set_mode(priv, LBTF_PASSIVE_MODE);
	lbtf_set_bssid(priv, 0, NULL);
	priv->vif = NULL;
	lbtf_deb_leave(LBTF_DEB_MACOPS);
}