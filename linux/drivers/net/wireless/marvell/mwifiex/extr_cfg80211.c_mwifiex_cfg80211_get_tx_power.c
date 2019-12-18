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
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct mwifiex_private {int tx_power_level; } ;
struct mwifiex_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HostCmd_ACT_GEN_GET ; 
 int /*<<< orphan*/  HostCmd_CMD_RF_TX_PWR ; 
 int /*<<< orphan*/  MWIFIEX_BSS_ROLE_ANY ; 
 struct mwifiex_adapter* mwifiex_cfg80211_get_adapter (struct wiphy*) ; 
 struct mwifiex_private* mwifiex_get_priv (struct mwifiex_adapter*,int /*<<< orphan*/ ) ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
mwifiex_cfg80211_get_tx_power(struct wiphy *wiphy,
			      struct wireless_dev *wdev,
			      int *dbm)
{
	struct mwifiex_adapter *adapter = mwifiex_cfg80211_get_adapter(wiphy);
	struct mwifiex_private *priv = mwifiex_get_priv(adapter,
							MWIFIEX_BSS_ROLE_ANY);
	int ret = mwifiex_send_cmd(priv, HostCmd_CMD_RF_TX_PWR,
				   HostCmd_ACT_GEN_GET, 0, NULL, true);

	if (ret < 0)
		return ret;

	/* tx_power_level is set in HostCmd_CMD_RF_TX_PWR command handler */
	*dbm = priv->tx_power_level;

	return 0;
}