#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iscsi_transport {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_attrs; } ;
struct iscsi_internal {TYPE_2__ dev; TYPE_1__ t; int /*<<< orphan*/  session_cont; int /*<<< orphan*/  conn_cont; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  device_unregister (TYPE_2__*) ; 
 struct iscsi_internal* iscsi_if_transport_lookup (struct iscsi_transport*) ; 
 int /*<<< orphan*/  iscsi_transport_group ; 
 int /*<<< orphan*/  iscsi_transport_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_queue_mutex ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transport_container_unregister (int /*<<< orphan*/ *) ; 

int iscsi_unregister_transport(struct iscsi_transport *tt)
{
	struct iscsi_internal *priv;
	unsigned long flags;

	BUG_ON(!tt);

	mutex_lock(&rx_queue_mutex);

	priv = iscsi_if_transport_lookup(tt);
	BUG_ON (!priv);

	spin_lock_irqsave(&iscsi_transport_lock, flags);
	list_del(&priv->list);
	spin_unlock_irqrestore(&iscsi_transport_lock, flags);

	transport_container_unregister(&priv->conn_cont);
	transport_container_unregister(&priv->session_cont);
	transport_container_unregister(&priv->t.host_attrs);

	sysfs_remove_group(&priv->dev.kobj, &iscsi_transport_group);
	device_unregister(&priv->dev);
	mutex_unlock(&rx_queue_mutex);

	return 0;
}