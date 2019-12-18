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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct r8192_priv {int basic_rate; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct ieee80211_network {int beacon_interval; scalar_t__ bssid; } ;
struct TYPE_2__ {scalar_t__ iw_mode; struct ieee80211_network current_network; } ;

/* Variables and functions */
 scalar_t__ ATIMWND ; 
 scalar_t__ BCN_DMATIME ; 
 scalar_t__ BCN_DRV_EARLY_INT ; 
 int /*<<< orphan*/  BCN_ERR_THRESH ; 
 scalar_t__ BCN_INTERVAL ; 
 scalar_t__ BCN_TCFG ; 
 int BCN_TCFG_CW_SHIFT ; 
 int BCN_TCFG_IFS ; 
 scalar_t__ BSSIDR ; 
 scalar_t__ IW_MODE_ADHOC ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_config_rate (struct net_device*,int*) ; 
 int /*<<< orphan*/  rtl8192_update_msr (struct net_device*) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,scalar_t__,int) ; 

__attribute__((used)) static void rtl8192_net_update(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	struct ieee80211_network *net;
	u16 BcnTimeCfg = 0, BcnCW = 6, BcnIFS = 0xf;
	u16 rate_config = 0;

	net = &priv->ieee80211->current_network;

	rtl8192_config_rate(dev, &rate_config);
	priv->basic_rate = rate_config & 0x15f;

	write_nic_dword(dev, BSSIDR, ((u32 *)net->bssid)[0]);
	write_nic_word(dev, BSSIDR + 4, ((u16 *)net->bssid)[2]);

	rtl8192_update_msr(dev);
	if (priv->ieee80211->iw_mode == IW_MODE_ADHOC) {
		write_nic_word(dev, ATIMWND, 2);
		write_nic_word(dev, BCN_DMATIME, 1023);
		write_nic_word(dev, BCN_INTERVAL, net->beacon_interval);
		write_nic_word(dev, BCN_DRV_EARLY_INT, 1);
		write_nic_byte(dev, BCN_ERR_THRESH, 100);
		BcnTimeCfg |= (BcnCW << BCN_TCFG_CW_SHIFT);
		/* TODO: BcnIFS may required to be changed on ASIC */
		BcnTimeCfg |= BcnIFS << BCN_TCFG_IFS;

		write_nic_word(dev, BCN_TCFG, BcnTimeCfg);
	}
}