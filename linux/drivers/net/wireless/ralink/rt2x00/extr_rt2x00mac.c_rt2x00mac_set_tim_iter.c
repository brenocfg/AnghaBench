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
typedef  int /*<<< orphan*/  u8 ;
struct rt2x00_intf {int /*<<< orphan*/  delayed_flags; } ;
struct ieee80211_vif {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAYED_UPDATE_BEACON ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_WDS ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rt2x00_intf* vif_to_intf (struct ieee80211_vif*) ; 

__attribute__((used)) static void rt2x00mac_set_tim_iter(void *data, u8 *mac,
				   struct ieee80211_vif *vif)
{
	struct rt2x00_intf *intf = vif_to_intf(vif);

	if (vif->type != NL80211_IFTYPE_AP &&
	    vif->type != NL80211_IFTYPE_ADHOC &&
	    vif->type != NL80211_IFTYPE_MESH_POINT &&
	    vif->type != NL80211_IFTYPE_WDS)
		return;

	set_bit(DELAYED_UPDATE_BEACON, &intf->delayed_flags);
}