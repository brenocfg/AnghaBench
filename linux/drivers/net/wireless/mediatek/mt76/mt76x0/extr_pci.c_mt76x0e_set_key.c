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
struct mt76x02_dev {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_key_conf {int dummy; } ;
struct ieee80211_hw {struct mt76x02_dev* priv; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ is_mt7630 (struct mt76x02_dev*) ; 
 int mt76x02_set_key (struct ieee80211_hw*,int,struct ieee80211_vif*,struct ieee80211_sta*,struct ieee80211_key_conf*) ; 

__attribute__((used)) static int
mt76x0e_set_key(struct ieee80211_hw *hw, enum set_key_cmd cmd,
		struct ieee80211_vif *vif, struct ieee80211_sta *sta,
		struct ieee80211_key_conf *key)
{
	struct mt76x02_dev *dev = hw->priv;

	if (is_mt7630(dev))
		return -EOPNOTSUPP;

	return mt76x02_set_key(hw, cmd, vif, sta, key);
}