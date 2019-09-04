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
struct fwnet_peer {struct fwnet_device* dev; } ;
struct fwnet_device {int /*<<< orphan*/  dev_link; scalar_t__ queued_datagrams; int /*<<< orphan*/  peer_list; struct net_device* netdev; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 struct fwnet_peer* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  fwnet_device_mutex ; 
 int /*<<< orphan*/  fwnet_fifo_stop (struct fwnet_device*) ; 
 int /*<<< orphan*/  fwnet_remove_peer (struct fwnet_peer*,struct fwnet_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void fwnet_remove(struct fw_unit *unit)
{
	struct fwnet_peer *peer = dev_get_drvdata(&unit->device);
	struct fwnet_device *dev = peer->dev;
	struct net_device *net;
	int i;

	mutex_lock(&fwnet_device_mutex);

	net = dev->netdev;

	fwnet_remove_peer(peer, dev);

	if (list_empty(&dev->peer_list)) {
		unregister_netdev(net);

		fwnet_fifo_stop(dev);

		for (i = 0; dev->queued_datagrams && i < 5; i++)
			ssleep(1);
		WARN_ON(dev->queued_datagrams);
		list_del(&dev->dev_link);

		free_netdev(net);
	}

	mutex_unlock(&fwnet_device_mutex);
}