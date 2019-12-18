#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct r8192_priv {int bDynamicTxHighPower; int bDynamicTxLowPower; unsigned int undecorated_smoothed_pwdb; int bLastDTPFlag_High; int bLastDTPFlag_Low; TYPE_3__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {unsigned int channel; } ;
struct TYPE_6__ {int bdynamic_txpower_enable; scalar_t__ mode; scalar_t__ state; TYPE_2__ current_network; TYPE_1__* pHTInfo; } ;
struct TYPE_4__ {scalar_t__ IOTPeer; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_TXAGC ; 
 scalar_t__ HT_IOT_PEER_ATHEROS ; 
 scalar_t__ IEEE_G ; 
 scalar_t__ RTLLIB_LINKED ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int TX_POWER_ATHEROAP_THRESH_HIGH ; 
 unsigned int TX_POWER_ATHEROAP_THRESH_LOW ; 
 unsigned int TX_POWER_NEAR_FIELD_THRESH_HIGH ; 
 unsigned int TX_POWER_NEAR_FIELD_THRESH_LOW ; 
 int /*<<< orphan*/  rtl92e_set_tx_power (struct net_device*,unsigned int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_dynamic_tx_power(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	unsigned int txhipower_threshhold = 0;
	unsigned int txlowpower_threshold = 0;

	if (priv->rtllib->bdynamic_txpower_enable != true) {
		priv->bDynamicTxHighPower = false;
		priv->bDynamicTxLowPower = false;
		return;
	}
	if ((priv->rtllib->pHTInfo->IOTPeer == HT_IOT_PEER_ATHEROS) &&
	    (priv->rtllib->mode == IEEE_G)) {
		txhipower_threshhold = TX_POWER_ATHEROAP_THRESH_HIGH;
		txlowpower_threshold = TX_POWER_ATHEROAP_THRESH_LOW;
	} else {
		txhipower_threshhold = TX_POWER_NEAR_FIELD_THRESH_HIGH;
		txlowpower_threshold = TX_POWER_NEAR_FIELD_THRESH_LOW;
	}

	RT_TRACE(COMP_TXAGC, "priv->undecorated_smoothed_pwdb = %ld\n",
		 priv->undecorated_smoothed_pwdb);

	if (priv->rtllib->state == RTLLIB_LINKED) {
		if (priv->undecorated_smoothed_pwdb >= txhipower_threshhold) {
			priv->bDynamicTxHighPower = true;
			priv->bDynamicTxLowPower = false;
		} else {
			if (priv->undecorated_smoothed_pwdb <
			    txlowpower_threshold && priv->bDynamicTxHighPower)
				priv->bDynamicTxHighPower = false;
			if (priv->undecorated_smoothed_pwdb < 35)
				priv->bDynamicTxLowPower = true;
			else if (priv->undecorated_smoothed_pwdb >= 40)
				priv->bDynamicTxLowPower = false;
		}
	} else {
		priv->bDynamicTxHighPower = false;
		priv->bDynamicTxLowPower = false;
	}

	if ((priv->bDynamicTxHighPower != priv->bLastDTPFlag_High) ||
	    (priv->bDynamicTxLowPower != priv->bLastDTPFlag_Low)) {
		RT_TRACE(COMP_TXAGC, "SetTxPowerLevel8190()  channel = %d\n",
			 priv->rtllib->current_network.channel);

		rtl92e_set_tx_power(dev, priv->rtllib->current_network.channel);
	}
	priv->bLastDTPFlag_High = priv->bDynamicTxHighPower;
	priv->bLastDTPFlag_Low = priv->bDynamicTxLowPower;

}