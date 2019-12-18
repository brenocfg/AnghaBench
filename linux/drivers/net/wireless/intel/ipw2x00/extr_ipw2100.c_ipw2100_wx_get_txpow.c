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
struct TYPE_2__ {int disabled; int fixed; scalar_t__ value; int /*<<< orphan*/  flags; } ;
union iwreq_data {TYPE_1__ txpower; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {int status; scalar_t__ tx_power; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,scalar_t__) ; 
 scalar_t__ IPW_TX_POWER_DEFAULT ; 
 scalar_t__ IPW_TX_POWER_MAX_DBM ; 
 int /*<<< orphan*/  IW_TXPOW_DBM ; 
 int STATUS_RF_KILL_MASK ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 

__attribute__((used)) static int ipw2100_wx_get_txpow(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	/*
	 * This can be called at any time.  No action lock required
	 */

	struct ipw2100_priv *priv = libipw_priv(dev);

	wrqu->txpower.disabled = (priv->status & STATUS_RF_KILL_MASK) ? 1 : 0;

	if (priv->tx_power == IPW_TX_POWER_DEFAULT) {
		wrqu->txpower.fixed = 0;
		wrqu->txpower.value = IPW_TX_POWER_MAX_DBM;
	} else {
		wrqu->txpower.fixed = 1;
		wrqu->txpower.value = priv->tx_power;
	}

	wrqu->txpower.flags = IW_TXPOW_DBM;

	IPW_DEBUG_WX("GET TX Power -> %d\n", wrqu->txpower.value);

	return 0;
}