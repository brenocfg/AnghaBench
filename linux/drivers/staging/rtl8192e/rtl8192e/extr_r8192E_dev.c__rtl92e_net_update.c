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
struct rtllib_network {int beacon_interval; scalar_t__ bssid; } ;
struct r8192_priv {int basic_rate; TYPE_1__* rtllib; int /*<<< orphan*/  dot11CurrentPreambleMode; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ iw_mode; struct rtllib_network current_network; } ;

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
 int /*<<< orphan*/  PREAMBLE_AUTO ; 
 int /*<<< orphan*/  rtl92e_config_rate (struct net_device*,int*) ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl92e_writel (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92e_writew (struct net_device*,scalar_t__,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_net_update(struct net_device *dev)
{

	struct r8192_priv *priv = rtllib_priv(dev);
	struct rtllib_network *net;
	u16 BcnTimeCfg = 0, BcnCW = 6, BcnIFS = 0xf;
	u16 rate_config = 0;

	net = &priv->rtllib->current_network;
	rtl92e_config_rate(dev, &rate_config);
	priv->dot11CurrentPreambleMode = PREAMBLE_AUTO;
	priv->basic_rate = rate_config &= 0x15f;
	rtl92e_writew(dev, BSSIDR, *(u16 *)net->bssid);
	rtl92e_writel(dev, BSSIDR + 2, *(u32 *)(net->bssid + 2));

	if (priv->rtllib->iw_mode == IW_MODE_ADHOC) {
		rtl92e_writew(dev, ATIMWND, 2);
		rtl92e_writew(dev, BCN_DMATIME, 256);
		rtl92e_writew(dev, BCN_INTERVAL, net->beacon_interval);
		rtl92e_writew(dev, BCN_DRV_EARLY_INT, 10);
		rtl92e_writeb(dev, BCN_ERR_THRESH, 100);

		BcnTimeCfg |= (BcnCW<<BCN_TCFG_CW_SHIFT);
		BcnTimeCfg |= BcnIFS<<BCN_TCFG_IFS;

		rtl92e_writew(dev, BCN_TCFG, BcnTimeCfg);
	}
}