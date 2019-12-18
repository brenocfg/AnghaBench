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
struct wcn36xx_sta {int /*<<< orphan*/  sta_index; int /*<<< orphan*/  bss_sta_index; } ;
struct ieee80211_vif {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 

__attribute__((used)) static inline u8 get_sta_index(struct ieee80211_vif *vif,
			       struct wcn36xx_sta *sta_priv)
{
	return NL80211_IFTYPE_STATION == vif->type ?
	       sta_priv->bss_sta_index :
	       sta_priv->sta_index;
}