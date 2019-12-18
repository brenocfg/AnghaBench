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
struct vnt_private {scalar_t__ PortOffset; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  beacon_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARDbSetBeaconPeriod (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CARDvSetFirstNextTBTT (struct vnt_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ MAC_REG_TFTCTL ; 
 int /*<<< orphan*/  TFTCTL_TSFCNTREN ; 
 int /*<<< orphan*/  TFTCTL_TSFCNTRST ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int /*<<< orphan*/ ) ; 
 int vnt_beacon_make (struct vnt_private*,struct ieee80211_vif*) ; 

int vnt_beacon_enable(struct vnt_private *priv, struct ieee80211_vif *vif,
		      struct ieee80211_bss_conf *conf)
{
	VNSvOutPortB(priv->PortOffset + MAC_REG_TFTCTL, TFTCTL_TSFCNTRST);

	VNSvOutPortB(priv->PortOffset + MAC_REG_TFTCTL, TFTCTL_TSFCNTREN);

	CARDvSetFirstNextTBTT(priv, conf->beacon_int);

	CARDbSetBeaconPeriod(priv, conf->beacon_int);

	return vnt_beacon_make(priv, vif);
}