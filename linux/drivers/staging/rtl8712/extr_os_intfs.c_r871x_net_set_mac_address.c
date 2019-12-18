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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct _adapter {int /*<<< orphan*/  bup; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct _adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int r871x_net_set_mac_address(struct net_device *pnetdev, void *p)
{
	struct _adapter *padapter = netdev_priv(pnetdev);
	struct sockaddr *addr = p;

	if (!padapter->bup)
		ether_addr_copy(pnetdev->dev_addr, addr->sa_data);
	return 0;
}