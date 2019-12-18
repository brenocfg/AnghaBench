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
typedef  int u32 ;
struct mt76x02_vif {int /*<<< orphan*/  idx; } ;
struct TYPE_2__ {int beacon_int; int /*<<< orphan*/  mutex; } ;
struct mt76x02_dev {int slottime; TYPE_1__ mt76; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct mt76x02_dev* priv; } ;
struct ieee80211_bss_conf {int beacon_int; scalar_t__ use_short_slot; int /*<<< orphan*/  use_short_preamble; int /*<<< orphan*/  enable_beacon; int /*<<< orphan*/  ht_operation_mode; int /*<<< orphan*/  use_cts_prot; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_BSSID ; 
 int BSS_CHANGED_ERP_CTS_PROT ; 
 int BSS_CHANGED_ERP_PREAMBLE ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int BSS_CHANGED_HT ; 
 int /*<<< orphan*/  MT_BEACON_TIME_CFG ; 
 int /*<<< orphan*/  MT_BEACON_TIME_CFG_INTVAL ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_mac_set_beacon_enable (struct mt76x02_dev*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_mac_set_bssid (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_mac_set_short_preamble (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_mac_set_tx_protection (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_set_tx_ackto (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mt76x02_bss_info_changed(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif,
			      struct ieee80211_bss_conf *info,
			      u32 changed)
{
	struct mt76x02_vif *mvif = (struct mt76x02_vif *)vif->drv_priv;
	struct mt76x02_dev *dev = hw->priv;

	mutex_lock(&dev->mt76.mutex);

	if (changed & BSS_CHANGED_BSSID)
		mt76x02_mac_set_bssid(dev, mvif->idx, info->bssid);

	if (changed & BSS_CHANGED_HT || changed & BSS_CHANGED_ERP_CTS_PROT)
		mt76x02_mac_set_tx_protection(dev, info->use_cts_prot,
					      info->ht_operation_mode);

	if (changed & BSS_CHANGED_BEACON_INT) {
		mt76_rmw_field(dev, MT_BEACON_TIME_CFG,
			       MT_BEACON_TIME_CFG_INTVAL,
			       info->beacon_int << 4);
		dev->mt76.beacon_int = info->beacon_int;
	}

	if (changed & BSS_CHANGED_BEACON_ENABLED)
		mt76x02_mac_set_beacon_enable(dev, vif, info->enable_beacon);

	if (changed & BSS_CHANGED_ERP_PREAMBLE)
		mt76x02_mac_set_short_preamble(dev, info->use_short_preamble);

	if (changed & BSS_CHANGED_ERP_SLOT) {
		int slottime = info->use_short_slot ? 9 : 20;

		dev->slottime = slottime;
		mt76x02_set_tx_ackto(dev);
	}

	mutex_unlock(&dev->mt76.mutex);
}