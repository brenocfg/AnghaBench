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
struct mt76_dev {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mt76_sta_remove (struct mt76_dev*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt76_sta_remove(struct mt76_dev *dev, struct ieee80211_vif *vif,
		struct ieee80211_sta *sta)
{
	mutex_lock(&dev->mutex);
	__mt76_sta_remove(dev, vif, sta);
	mutex_unlock(&dev->mutex);
}