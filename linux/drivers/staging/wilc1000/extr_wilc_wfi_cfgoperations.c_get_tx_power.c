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
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {int /*<<< orphan*/  netdev; } ;
struct wiphy {int dummy; } ;
struct wilc_vif {int /*<<< orphan*/  ndev; struct wilc* wilc; } ;
struct wilc {int /*<<< orphan*/  initialized; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int wilc_get_tx_power (struct wilc_vif*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_tx_power(struct wiphy *wiphy, struct wireless_dev *wdev,
			int *dbm)
{
	int ret;
	struct wilc_vif *vif = netdev_priv(wdev->netdev);
	struct wilc *wl = vif->wilc;

	/* If firmware is not started, return. */
	if (!wl->initialized)
		return -EIO;

	ret = wilc_get_tx_power(vif, (u8 *)dbm);
	if (ret)
		netdev_err(vif->ndev, "Failed to get tx power\n");

	return ret;
}