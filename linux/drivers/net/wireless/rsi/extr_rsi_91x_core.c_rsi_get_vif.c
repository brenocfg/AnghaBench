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
struct rsi_hw {struct ieee80211_vif** vifs; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int RSI_MAX_VIFS ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct ieee80211_vif *rsi_get_vif(struct rsi_hw *adapter, u8 *mac)
{
	struct ieee80211_vif *vif;
	int i;

	for (i = 0; i < RSI_MAX_VIFS; i++) {
		vif = adapter->vifs[i];
		if (!vif)
			continue;
		if (!memcmp(vif->addr, mac, ETH_ALEN))
			return vif;
	}
	return NULL;
}