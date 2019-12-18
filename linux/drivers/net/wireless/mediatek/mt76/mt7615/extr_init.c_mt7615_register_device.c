#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wiphy {int interface_modes; int /*<<< orphan*/  flags; int /*<<< orphan*/  reg_notifier; int /*<<< orphan*/  n_iface_combinations; int /*<<< orphan*/  iface_combinations; } ;
struct mt7615_vif {int dummy; } ;
struct mt7615_sta {int dummy; } ;
struct TYPE_8__ {int cap; } ;
struct TYPE_7__ {int /*<<< orphan*/  cap; } ;
struct TYPE_12__ {TYPE_2__ vht_cap; TYPE_1__ ht_cap; } ;
struct TYPE_10__ {TYPE_6__ sband; } ;
struct TYPE_9__ {TYPE_6__ sband; } ;
struct TYPE_11__ {int chainmask; int antenna_mask; TYPE_4__ sband_5g; TYPE_3__ sband_2g; int /*<<< orphan*/  mac_work; } ;
struct mt7615_dev {int dfs_state; TYPE_5__ mt76; } ;
struct ieee80211_hw {int queues; int max_rates; int max_report_rates; int max_rate_tries; int sta_data_size; int vif_data_size; int /*<<< orphan*/  max_tx_fragments; struct wiphy* wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_LDPC_CODING ; 
 int IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK ; 
 int IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454 ; 
 int IEEE80211_VHT_CAP_SHORT_GI_160 ; 
 int IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_TXP_MAX_BUF_NUM ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  SUPPORTS_REORDERING_BUFFER ; 
 int /*<<< orphan*/  TX_STATUS_NO_AMPDU_LEN ; 
 int /*<<< orphan*/  WIPHY_FLAG_HAS_CHANNEL_SWITCH ; 
 int /*<<< orphan*/  ieee80211_hw_set (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_comb ; 
 int mt7615_init_debugfs (struct mt7615_dev*) ; 
 int mt7615_init_hardware (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt7615_init_txpower (struct mt7615_dev*,TYPE_6__*) ; 
 int /*<<< orphan*/  mt7615_mac_work ; 
 int /*<<< orphan*/  mt7615_rates ; 
 int /*<<< orphan*/  mt7615_regd_notifier ; 
 struct ieee80211_hw* mt76_hw (struct mt7615_dev*) ; 
 int mt76_register_device (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mt7615_register_device(struct mt7615_dev *dev)
{
	struct ieee80211_hw *hw = mt76_hw(dev);
	struct wiphy *wiphy = hw->wiphy;
	int ret;

	ret = mt7615_init_hardware(dev);
	if (ret)
		return ret;

	INIT_DELAYED_WORK(&dev->mt76.mac_work, mt7615_mac_work);

	hw->queues = 4;
	hw->max_rates = 3;
	hw->max_report_rates = 7;
	hw->max_rate_tries = 11;

	hw->sta_data_size = sizeof(struct mt7615_sta);
	hw->vif_data_size = sizeof(struct mt7615_vif);

	wiphy->iface_combinations = if_comb;
	wiphy->n_iface_combinations = ARRAY_SIZE(if_comb);
	wiphy->reg_notifier = mt7615_regd_notifier;
	wiphy->flags |= WIPHY_FLAG_HAS_CHANNEL_SWITCH;

	ieee80211_hw_set(hw, SUPPORTS_REORDERING_BUFFER);
	ieee80211_hw_set(hw, TX_STATUS_NO_AMPDU_LEN);

	dev->mt76.sband_2g.sband.ht_cap.cap |= IEEE80211_HT_CAP_LDPC_CODING;
	dev->mt76.sband_5g.sband.ht_cap.cap |= IEEE80211_HT_CAP_LDPC_CODING;
	dev->mt76.sband_5g.sband.vht_cap.cap |=
			IEEE80211_VHT_CAP_SHORT_GI_160 |
			IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454 |
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK |
			IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ;
	dev->mt76.chainmask = 0x404;
	dev->mt76.antenna_mask = 0xf;
	dev->dfs_state = -1;

	wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION) |
#ifdef CONFIG_MAC80211_MESH
				 BIT(NL80211_IFTYPE_MESH_POINT) |
#endif
				 BIT(NL80211_IFTYPE_AP);

	ret = mt76_register_device(&dev->mt76, true, mt7615_rates,
				   ARRAY_SIZE(mt7615_rates));
	if (ret)
		return ret;

	mt7615_init_txpower(dev, &dev->mt76.sband_2g.sband);
	mt7615_init_txpower(dev, &dev->mt76.sband_5g.sband);

	hw->max_tx_fragments = MT_TXP_MAX_BUF_NUM;

	return mt7615_init_debugfs(dev);
}