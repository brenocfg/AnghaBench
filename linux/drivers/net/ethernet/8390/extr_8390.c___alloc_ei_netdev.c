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
struct net_device {int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 struct net_device* ____alloc_ei_netdev (int) ; 
 int /*<<< orphan*/  ei_netdev_ops ; 

struct net_device *__alloc_ei_netdev(int size)
{
	struct net_device *dev = ____alloc_ei_netdev(size);
	if (dev)
		dev->netdev_ops = &ei_netdev_ops;
	return dev;
}