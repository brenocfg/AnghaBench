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
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct bdx_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  RET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdx_restore_mac (struct net_device*,struct bdx_priv*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bdx_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bdx_set_mac(struct net_device *ndev, void *p)
{
	struct bdx_priv *priv = netdev_priv(ndev);
	struct sockaddr *addr = p;

	ENTER;
	/*
	   if (netif_running(dev))
	   return -EBUSY
	 */
	memcpy(ndev->dev_addr, addr->sa_data, ndev->addr_len);
	bdx_restore_mac(ndev, priv);
	RET(0);
}