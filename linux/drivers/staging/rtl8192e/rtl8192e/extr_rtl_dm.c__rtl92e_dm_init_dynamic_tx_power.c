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
struct r8192_priv {int bLastDTPFlag_High; int bLastDTPFlag_Low; int bDynamicTxHighPower; int bDynamicTxLowPower; TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int bdynamic_txpower_enable; } ;

/* Variables and functions */
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_init_dynamic_tx_power(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	priv->rtllib->bdynamic_txpower_enable = true;
	priv->bLastDTPFlag_High = false;
	priv->bLastDTPFlag_Low = false;
	priv->bDynamicTxHighPower = false;
	priv->bDynamicTxLowPower = false;
}