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
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  sopass; int /*<<< orphan*/  wolopts; int /*<<< orphan*/  supported; } ;
struct dev_priv {struct dev_info* adapter; } ;
struct dev_info {int /*<<< orphan*/  wol_enable; int /*<<< orphan*/  wol_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void netdev_get_wol(struct net_device *dev,
	struct ethtool_wolinfo *wol)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;

	wol->supported = hw_priv->wol_support;
	wol->wolopts = hw_priv->wol_enable;
	memset(&wol->sopass, 0, sizeof(wol->sopass));
}