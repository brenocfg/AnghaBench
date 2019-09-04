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
struct netdev_private {scalar_t__ rx_buf_sz; } ;
struct net_device {scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ ETH_DATA_LEN ; 
 scalar_t__ NATSEMI_HEADERS ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void set_bufsize(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	if (dev->mtu <= ETH_DATA_LEN)
		np->rx_buf_sz = ETH_DATA_LEN + NATSEMI_HEADERS;
	else
		np->rx_buf_sz = dev->mtu + NATSEMI_HEADERS;
}