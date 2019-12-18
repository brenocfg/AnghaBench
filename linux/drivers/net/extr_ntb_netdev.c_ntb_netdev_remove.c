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
struct ntb_netdev {int /*<<< orphan*/  qp; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct ntb_netdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ntb_transport_free_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void ntb_netdev_remove(struct device *client_dev)
{
	struct net_device *ndev = dev_get_drvdata(client_dev);
	struct ntb_netdev *dev = netdev_priv(ndev);

	unregister_netdev(ndev);
	ntb_transport_free_queue(dev->qp);
	free_netdev(ndev);
}