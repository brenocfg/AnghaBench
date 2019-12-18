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
struct myri10ge_priv {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int myri10ge_update_mac_address (struct myri10ge_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct myri10ge_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int myri10ge_set_mac_address(struct net_device *dev, void *addr)
{
	struct sockaddr *sa = addr;
	struct myri10ge_priv *mgp = netdev_priv(dev);
	int status;

	if (!is_valid_ether_addr(sa->sa_data))
		return -EADDRNOTAVAIL;

	status = myri10ge_update_mac_address(mgp, sa->sa_data);
	if (status != 0) {
		netdev_err(dev, "changing mac address failed with %d\n",
			   status);
		return status;
	}

	/* change the dev structure */
	memcpy(dev->dev_addr, sa->sa_data, ETH_ALEN);
	return 0;
}