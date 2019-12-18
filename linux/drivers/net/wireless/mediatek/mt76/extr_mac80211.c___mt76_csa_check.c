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
struct mt76_dev {int /*<<< orphan*/  csa_complete; } ;
struct ieee80211_vif {int /*<<< orphan*/  csa_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_csa_is_complete (struct ieee80211_vif*) ; 

__attribute__((used)) static void
__mt76_csa_check(void *priv, u8 *mac, struct ieee80211_vif *vif)
{
	struct mt76_dev *dev = priv;

	if (!vif->csa_active)
		return;

	dev->csa_complete |= ieee80211_csa_is_complete(vif);
}