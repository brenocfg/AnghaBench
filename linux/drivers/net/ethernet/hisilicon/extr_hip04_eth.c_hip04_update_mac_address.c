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
struct net_device {int* dev_addr; } ;
struct hip04_priv {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ GE_STATION_MAC_ADDRESS ; 
 struct hip04_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void hip04_update_mac_address(struct net_device *ndev)
{
	struct hip04_priv *priv = netdev_priv(ndev);

	writel_relaxed(((ndev->dev_addr[0] << 8) | (ndev->dev_addr[1])),
		       priv->base + GE_STATION_MAC_ADDRESS);
	writel_relaxed(((ndev->dev_addr[2] << 24) | (ndev->dev_addr[3] << 16) |
			(ndev->dev_addr[4] << 8) | (ndev->dev_addr[5])),
		       priv->base + GE_STATION_MAC_ADDRESS + 4);
}