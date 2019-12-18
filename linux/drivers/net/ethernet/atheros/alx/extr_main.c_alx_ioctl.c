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
struct net_device {int dummy; } ;
struct ifreq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdio; } ;
struct alx_priv {TYPE_1__ hw; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 
 int mdio_mii_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct alx_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static int alx_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd)
{
	struct alx_priv *alx = netdev_priv(netdev);

	if (!netif_running(netdev))
		return -EAGAIN;

	return mdio_mii_ioctl(&alx->hw.mdio, if_mii(ifr), cmd);
}