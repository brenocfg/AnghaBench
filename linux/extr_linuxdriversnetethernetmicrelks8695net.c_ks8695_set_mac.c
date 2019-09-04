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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; int /*<<< orphan*/  addr_len; } ;
struct ks8695_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks8695_update_mac (struct ks8695_priv*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ks8695_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
ks8695_set_mac(struct net_device *ndev, void *addr)
{
	struct ks8695_priv *ksp = netdev_priv(ndev);
	struct sockaddr *address = addr;

	if (!is_valid_ether_addr(address->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(ndev->dev_addr, address->sa_data, ndev->addr_len);

	ks8695_update_mac(ksp);

	dev_dbg(ksp->dev, "%s: Updated MAC address to %pM\n",
		ndev->name, ndev->dev_addr);

	return 0;
}