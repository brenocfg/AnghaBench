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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ rx_cnt; scalar_t__ tx_cnt; scalar_t__ rx_unicast; scalar_t__ tx_unicast; } ;
struct rtw_vif {size_t port; int in_lps; int net_type; size_t bcn_ctrl; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/ * conf; TYPE_1__ stats; struct ieee80211_vif* vif; } ;
struct rtw_dev {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int type; int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct rtw_dev* priv; } ;
typedef  enum rtw_net_type { ____Placeholder_rtw_net_type } rtw_net_type ;

/* Variables and functions */
 size_t BIT_DIS_TSF_UDT ; 
 size_t BIT_EN_BCN_FUNCTION ; 
#define  NL80211_IFTYPE_ADHOC 131 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MESH_POINT 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  PORT_SET_BCN_CTRL ; 
 int /*<<< orphan*/  PORT_SET_MAC_ADDR ; 
 int /*<<< orphan*/  PORT_SET_NET_TYPE ; 
 int RTW_NET_AD_HOC ; 
 int RTW_NET_AP_MODE ; 
 int RTW_NET_NO_LINK ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_info (struct rtw_dev*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * rtw_vif_port ; 
 int /*<<< orphan*/  rtw_vif_port_config (struct rtw_dev*,struct rtw_vif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtw_ops_add_interface(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif)
{
	struct rtw_dev *rtwdev = hw->priv;
	struct rtw_vif *rtwvif = (struct rtw_vif *)vif->drv_priv;
	enum rtw_net_type net_type;
	u32 config = 0;
	u8 port = 0;
	u8 bcn_ctrl = 0;

	rtwvif->port = port;
	rtwvif->vif = vif;
	rtwvif->stats.tx_unicast = 0;
	rtwvif->stats.rx_unicast = 0;
	rtwvif->stats.tx_cnt = 0;
	rtwvif->stats.rx_cnt = 0;
	rtwvif->in_lps = false;
	rtwvif->conf = &rtw_vif_port[port];

	mutex_lock(&rtwdev->mutex);

	switch (vif->type) {
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_MESH_POINT:
		net_type = RTW_NET_AP_MODE;
		bcn_ctrl = BIT_EN_BCN_FUNCTION | BIT_DIS_TSF_UDT;
		break;
	case NL80211_IFTYPE_ADHOC:
		net_type = RTW_NET_AD_HOC;
		bcn_ctrl = BIT_EN_BCN_FUNCTION | BIT_DIS_TSF_UDT;
		break;
	case NL80211_IFTYPE_STATION:
	default:
		net_type = RTW_NET_NO_LINK;
		bcn_ctrl = BIT_EN_BCN_FUNCTION;
		break;
	}

	ether_addr_copy(rtwvif->mac_addr, vif->addr);
	config |= PORT_SET_MAC_ADDR;
	rtwvif->net_type = net_type;
	config |= PORT_SET_NET_TYPE;
	rtwvif->bcn_ctrl = bcn_ctrl;
	config |= PORT_SET_BCN_CTRL;
	rtw_vif_port_config(rtwdev, rtwvif, config);

	mutex_unlock(&rtwdev->mutex);

	rtw_info(rtwdev, "start vif %pM on port %d\n", vif->addr, rtwvif->port);
	return 0;
}