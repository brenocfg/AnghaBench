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
struct virtnet_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  failover; int /*<<< orphan*/  config_work; } ;
struct virtio_device {struct virtnet_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_failover_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_vq_common (struct virtnet_info*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtnet_cpu_notif_remove (struct virtnet_info*) ; 

__attribute__((used)) static void virtnet_remove(struct virtio_device *vdev)
{
	struct virtnet_info *vi = vdev->priv;

	virtnet_cpu_notif_remove(vi);

	/* Make sure no work handler is accessing the device. */
	flush_work(&vi->config_work);

	unregister_netdev(vi->dev);

	net_failover_destroy(vi->failover);

	remove_vq_common(vi);

	free_netdev(vi->dev);
}