#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rtw_vif {int dummy; } ;
struct rtw_sta_info {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  alpha2; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct rtw_dev {TYPE_2__ regd; TYPE_1__ efuse; TYPE_3__* chip; } ;
struct ieee80211_hw {int extra_tx_headroom; int sta_data_size; int vif_data_size; TYPE_4__* wiphy; int /*<<< orphan*/  queues; } ;
struct TYPE_8__ {int interface_modes; int flags; int /*<<< orphan*/  features; } ;
struct TYPE_7__ {int tx_pkt_desc_sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMPDU_AGGREGATION ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  MFP_CAPABLE ; 
 int /*<<< orphan*/  NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  REPORTS_TX_ACK_STATUS ; 
 int /*<<< orphan*/  RX_INCLUDES_FCS ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGNAL_DBM ; 
 int /*<<< orphan*/  SUPPORTS_AMSDU_IN_AMPDU ; 
 int /*<<< orphan*/  SUPPORTS_DYNAMIC_PS ; 
 int /*<<< orphan*/  SUPPORTS_PS ; 
 int /*<<< orphan*/  SUPPORT_FAST_XMIT ; 
 int WIPHY_FLAG_SUPPORTS_TDLS ; 
 int WIPHY_FLAG_TDLS_EXTERNAL_SETUP ; 
 int /*<<< orphan*/  ieee80211_hw_set (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int ieee80211_register_hw (struct ieee80211_hw*) ; 
 scalar_t__ regulatory_hint (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_debugfs_init (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int /*<<< orphan*/  rtw_regd_init (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_regd_notifier ; 
 int /*<<< orphan*/  rtw_set_supported_band (struct ieee80211_hw*,TYPE_3__*) ; 

int rtw_register_hw(struct rtw_dev *rtwdev, struct ieee80211_hw *hw)
{
	int max_tx_headroom = 0;
	int ret;

	/* TODO: USB & SDIO may need extra room? */
	max_tx_headroom = rtwdev->chip->tx_pkt_desc_sz;

	hw->extra_tx_headroom = max_tx_headroom;
	hw->queues = IEEE80211_NUM_ACS;
	hw->sta_data_size = sizeof(struct rtw_sta_info);
	hw->vif_data_size = sizeof(struct rtw_vif);

	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, MFP_CAPABLE);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, SUPPORTS_PS);
	ieee80211_hw_set(hw, SUPPORTS_DYNAMIC_PS);
	ieee80211_hw_set(hw, SUPPORT_FAST_XMIT);
	ieee80211_hw_set(hw, SUPPORTS_AMSDU_IN_AMPDU);

	hw->wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION) |
				     BIT(NL80211_IFTYPE_AP) |
				     BIT(NL80211_IFTYPE_ADHOC) |
				     BIT(NL80211_IFTYPE_MESH_POINT);

	hw->wiphy->flags |= WIPHY_FLAG_SUPPORTS_TDLS |
			    WIPHY_FLAG_TDLS_EXTERNAL_SETUP;

	hw->wiphy->features |= NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR;

	rtw_set_supported_band(hw, rtwdev->chip);
	SET_IEEE80211_PERM_ADDR(hw, rtwdev->efuse.addr);

	rtw_regd_init(rtwdev, rtw_regd_notifier);

	ret = ieee80211_register_hw(hw);
	if (ret) {
		rtw_err(rtwdev, "failed to register hw\n");
		return ret;
	}

	if (regulatory_hint(hw->wiphy, rtwdev->regd.alpha2))
		rtw_err(rtwdev, "regulatory_hint fail\n");

	rtw_debugfs_init(rtwdev);

	return 0;
}