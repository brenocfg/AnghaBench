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
struct ssb_sprom {int /*<<< orphan*/  il0mac; int /*<<< orphan*/  et1mac; } ;
struct ieee80211_hw {int max_rates; TYPE_1__* wiphy; } ;
struct b43_wl {int hw_registered; scalar_t__* tx_queue_stopped; int /*<<< orphan*/ * tx_queue; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  txpower_adjust_work; int /*<<< orphan*/  beacon_update_trigger; int /*<<< orphan*/  beacon_lock; int /*<<< orphan*/  hardirq_lock; int /*<<< orphan*/  mutex; struct ieee80211_hw* hw; } ;
struct b43_bus_dev {int chip_id; int /*<<< orphan*/  core_rev; int /*<<< orphan*/  dev; struct ssb_sprom* bus_sprom; } ;
struct TYPE_2__ {int interface_modes; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int B43_QOS_QUEUE_NUM ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct b43_wl* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_CQM_RSSI_LIST ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  NL80211_IFTYPE_WDS ; 
 int /*<<< orphan*/  RX_INCLUDES_FCS ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGNAL_DBM ; 
 int /*<<< orphan*/  WIPHY_FLAG_IBSS_RSN ; 
 int /*<<< orphan*/  b43_beacon_update_trigger_work ; 
 int /*<<< orphan*/  b43_hw_ops ; 
 int /*<<< orphan*/  b43_phy_txpower_adjust_work ; 
 int /*<<< orphan*/  b43_tx_work ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  b43info (struct b43_wl*,char*,char*,int /*<<< orphan*/ ) ; 
 struct b43_wl* hw_to_b43_wl (struct ieee80211_hw*) ; 
 struct ieee80211_hw* ieee80211_alloc_hw (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_hw_set (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_ext_feature_set (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct b43_wl *b43_wireless_init(struct b43_bus_dev *dev)
{
	struct ssb_sprom *sprom = dev->bus_sprom;
	struct ieee80211_hw *hw;
	struct b43_wl *wl;
	char chip_name[6];
	int queue_num;

	hw = ieee80211_alloc_hw(sizeof(*wl), &b43_hw_ops);
	if (!hw) {
		b43err(NULL, "Could not allocate ieee80211 device\n");
		return ERR_PTR(-ENOMEM);
	}
	wl = hw_to_b43_wl(hw);

	/* fill hw info */
	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, SIGNAL_DBM);

	hw->wiphy->interface_modes =
		BIT(NL80211_IFTYPE_AP) |
		BIT(NL80211_IFTYPE_MESH_POINT) |
		BIT(NL80211_IFTYPE_STATION) |
#ifdef CONFIG_WIRELESS_WDS
		BIT(NL80211_IFTYPE_WDS) |
#endif
		BIT(NL80211_IFTYPE_ADHOC);

	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	wl->hw_registered = false;
	hw->max_rates = 2;
	SET_IEEE80211_DEV(hw, dev->dev);
	if (is_valid_ether_addr(sprom->et1mac))
		SET_IEEE80211_PERM_ADDR(hw, sprom->et1mac);
	else
		SET_IEEE80211_PERM_ADDR(hw, sprom->il0mac);

	/* Initialize struct b43_wl */
	wl->hw = hw;
	mutex_init(&wl->mutex);
	spin_lock_init(&wl->hardirq_lock);
	spin_lock_init(&wl->beacon_lock);
	INIT_WORK(&wl->beacon_update_trigger, b43_beacon_update_trigger_work);
	INIT_WORK(&wl->txpower_adjust_work, b43_phy_txpower_adjust_work);
	INIT_WORK(&wl->tx_work, b43_tx_work);

	/* Initialize queues and flags. */
	for (queue_num = 0; queue_num < B43_QOS_QUEUE_NUM; queue_num++) {
		skb_queue_head_init(&wl->tx_queue[queue_num]);
		wl->tx_queue_stopped[queue_num] = 0;
	}

	snprintf(chip_name, ARRAY_SIZE(chip_name),
		 (dev->chip_id > 0x9999) ? "%d" : "%04X", dev->chip_id);
	b43info(wl, "Broadcom %s WLAN found (core revision %u)\n", chip_name,
		dev->core_rev);
	return wl;
}