#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct vnet_port {TYPE_1__ vio; int /*<<< orphan*/  napi; int /*<<< orphan*/  clean_timer; int /*<<< orphan*/  hash; int /*<<< orphan*/  list; } ;
struct vio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct vnet_port* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vnet_port*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunvnet_port_free_tx_bufs_common (struct vnet_port*) ; 
 int /*<<< orphan*/  sunvnet_port_rm_txq_common (struct vnet_port*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  vio_ldc_free (TYPE_1__*) ; 

__attribute__((used)) static int vnet_port_remove(struct vio_dev *vdev)
{
	struct vnet_port *port = dev_get_drvdata(&vdev->dev);

	if (port) {
		del_timer_sync(&port->vio.timer);

		napi_disable(&port->napi);

		list_del_rcu(&port->list);
		hlist_del_rcu(&port->hash);

		synchronize_rcu();
		del_timer_sync(&port->clean_timer);
		sunvnet_port_rm_txq_common(port);
		netif_napi_del(&port->napi);
		sunvnet_port_free_tx_bufs_common(port);
		vio_ldc_free(&port->vio);

		dev_set_drvdata(&vdev->dev, NULL);

		kfree(port);
	}
	return 0;
}