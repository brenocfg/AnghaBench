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
struct enc28j60_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enc28j60_hw_disable (struct enc28j60_net*) ; 
 int /*<<< orphan*/  enc28j60_lowpower (struct enc28j60_net*,int) ; 
 struct enc28j60_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int enc28j60_net_close(struct net_device *dev)
{
	struct enc28j60_net *priv = netdev_priv(dev);

	enc28j60_hw_disable(priv);
	enc28j60_lowpower(priv, true);
	netif_stop_queue(dev);

	return 0;
}