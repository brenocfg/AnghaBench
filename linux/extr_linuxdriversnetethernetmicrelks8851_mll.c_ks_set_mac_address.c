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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {scalar_t__ dev_addr; int /*<<< orphan*/  addr_len; } ;
struct ks_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ks_set_mac (struct ks_net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ks_net* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_set_mac_address(struct net_device *netdev, void *paddr)
{
	struct ks_net *ks = netdev_priv(netdev);
	struct sockaddr *addr = paddr;
	u8 *da;

	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);

	da = (u8 *)netdev->dev_addr;

	ks_set_mac(ks, da);
	return 0;
}