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
typedef  int /*<<< orphan*/  u32 ;
struct wiphy {int dummy; } ;
struct rndis_wlan_private {scalar_t__ last_cqm_event_rssi; int /*<<< orphan*/  cqm_rssi_hyst; int /*<<< orphan*/  cqm_rssi_thold; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 struct rndis_wlan_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int rndis_set_cqm_rssi_config(struct wiphy *wiphy,
					struct net_device *dev,
					s32 rssi_thold, u32 rssi_hyst)
{
	struct rndis_wlan_private *priv = wiphy_priv(wiphy);

	priv->cqm_rssi_thold = rssi_thold;
	priv->cqm_rssi_hyst = rssi_hyst;
	priv->last_cqm_event_rssi = 0;

	return 0;
}