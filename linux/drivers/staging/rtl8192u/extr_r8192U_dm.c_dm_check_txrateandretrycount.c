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
struct r8192_priv {struct ieee80211_device* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  txretrycount; int /*<<< orphan*/  last_packet_rate; int /*<<< orphan*/  CurrentShowTxate; } ;
struct ieee80211_device {TYPE_1__ softmac_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TX_RATE_REG ; 
 int /*<<< orphan*/  INITIAL_TX_RATE_REG ; 
 int /*<<< orphan*/  TX_RETRY_COUNT_REG ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  read_nic_byte (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_nic_dword (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dm_check_txrateandretrycount(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	struct ieee80211_device *ieee = priv->ieee80211;
	/* for 11n tx rate */
	/*priv->stats.CurrentShowTxate = read_nic_byte(dev, CURRENT_TX_RATE_REG);*/
	read_nic_byte(dev, CURRENT_TX_RATE_REG, &ieee->softmac_stats.CurrentShowTxate);
	/*printk("=============>tx_rate_reg:%x\n", ieee->softmac_stats.CurrentShowTxate);*/
	/* for initial tx rate */
	/*priv->stats.last_packet_rate = read_nic_byte(dev, INITIAL_TX_RATE_REG);*/
	read_nic_byte(dev, INITIAL_TX_RATE_REG, &ieee->softmac_stats.last_packet_rate);
	/* for tx tx retry count */
	/*priv->stats.txretrycount = read_nic_dword(dev, TX_RETRY_COUNT_REG);*/
	read_nic_dword(dev, TX_RETRY_COUNT_REG, &ieee->softmac_stats.txretrycount);
}