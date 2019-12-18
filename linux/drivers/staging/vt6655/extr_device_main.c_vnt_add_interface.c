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
struct vnt_private {int op_mode; int /*<<< orphan*/  PortOffset; struct ieee80211_vif* vif; } ;
struct ieee80211_vif {int type; } ;
struct ieee80211_hw {struct vnt_private* priv; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HOSTCR_ADHOC ; 
 int /*<<< orphan*/  HOSTCR_AP ; 
 int /*<<< orphan*/  MAC_REG_HOSTCR ; 
 int /*<<< orphan*/  MAC_REG_RCR ; 
 int /*<<< orphan*/  MACvRegBitsOff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvRegBitsOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NL80211_IFTYPE_ADHOC 130 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  RCR_UNICAST ; 

__attribute__((used)) static int vnt_add_interface(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct vnt_private *priv = hw->priv;

	priv->vif = vif;

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		break;
	case NL80211_IFTYPE_ADHOC:
		MACvRegBitsOff(priv->PortOffset, MAC_REG_RCR, RCR_UNICAST);

		MACvRegBitsOn(priv->PortOffset, MAC_REG_HOSTCR, HOSTCR_ADHOC);

		break;
	case NL80211_IFTYPE_AP:
		MACvRegBitsOff(priv->PortOffset, MAC_REG_RCR, RCR_UNICAST);

		MACvRegBitsOn(priv->PortOffset, MAC_REG_HOSTCR, HOSTCR_AP);

		break;
	default:
		return -EOPNOTSUPP;
	}

	priv->op_mode = vif->type;

	return 0;
}