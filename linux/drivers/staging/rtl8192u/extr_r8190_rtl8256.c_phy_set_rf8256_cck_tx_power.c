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
typedef  int u8 ;
typedef  int u32 ;
struct r8192_priv {scalar_t__ CustomerID; scalar_t__ CckPwEnl; scalar_t__ bDynamicTxLowPower; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RT_CID_819x_Netcore ; 
 int /*<<< orphan*/  bTxAGCRateCCK ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rTxAGC_CCK_Mcs32 ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void phy_set_rf8256_cck_tx_power(struct net_device *dev, u8 powerlevel)
{
	u32	TxAGC = 0;
	struct r8192_priv *priv = ieee80211_priv(dev);

	TxAGC = powerlevel;

	if (priv->bDynamicTxLowPower) {
		if (priv->CustomerID == RT_CID_819x_Netcore)
			TxAGC = 0x22;
		else
			TxAGC += priv->CckPwEnl;
	}

	if (TxAGC > 0x24)
		TxAGC = 0x24;
	rtl8192_setBBreg(dev, rTxAGC_CCK_Mcs32, bTxAGCRateCCK, TxAGC);
}