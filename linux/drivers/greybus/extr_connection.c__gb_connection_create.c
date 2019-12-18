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
struct gb_interface {int quirks; int /*<<< orphan*/  dev; } ;
struct gb_host_device {int /*<<< orphan*/  connections; int /*<<< orphan*/  dev; } ;
struct gb_connection {int hd_cport_id; int intf_cport_id; unsigned long flags; int /*<<< orphan*/  bundle_links; int /*<<< orphan*/  hd_links; int /*<<< orphan*/  kref; int /*<<< orphan*/  wq; int /*<<< orphan*/  operations; int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  op_cycle; int /*<<< orphan*/  state; int /*<<< orphan*/  handler; struct gb_bundle* bundle; struct gb_interface* intf; struct gb_host_device* hd; } ;
struct gb_bundle {int /*<<< orphan*/  connections; } ;
typedef  int /*<<< orphan*/  gb_request_handler_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 struct gb_connection* ERR_PTR (int) ; 
 unsigned long GB_CONNECTION_FLAG_NO_FLOWCTRL ; 
 int /*<<< orphan*/  GB_CONNECTION_STATE_DISABLED ; 
 int GB_INTERFACE_QUIRK_NO_CPORT_FEATURES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WQ_UNBOUND ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ gb_connection_cport_in_use (struct gb_interface*,int) ; 
 int /*<<< orphan*/  gb_connection_init_name (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_mutex ; 
 int /*<<< orphan*/  gb_connections_lock ; 
 int gb_hd_cport_allocate (struct gb_host_device*,int,unsigned long) ; 
 int /*<<< orphan*/  gb_hd_cport_release (struct gb_host_device*,int) ; 
 int /*<<< orphan*/  kfree (struct gb_connection*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct gb_connection* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_gb_connection_create (struct gb_connection*) ; 

__attribute__((used)) static struct gb_connection *
_gb_connection_create(struct gb_host_device *hd, int hd_cport_id,
		      struct gb_interface *intf,
		      struct gb_bundle *bundle, int cport_id,
		      gb_request_handler_t handler,
		      unsigned long flags)
{
	struct gb_connection *connection;
	int ret;

	mutex_lock(&gb_connection_mutex);

	if (intf && gb_connection_cport_in_use(intf, cport_id)) {
		dev_err(&intf->dev, "cport %u already in use\n", cport_id);
		ret = -EBUSY;
		goto err_unlock;
	}

	ret = gb_hd_cport_allocate(hd, hd_cport_id, flags);
	if (ret < 0) {
		dev_err(&hd->dev, "failed to allocate cport: %d\n", ret);
		goto err_unlock;
	}
	hd_cport_id = ret;

	connection = kzalloc(sizeof(*connection), GFP_KERNEL);
	if (!connection) {
		ret = -ENOMEM;
		goto err_hd_cport_release;
	}

	connection->hd_cport_id = hd_cport_id;
	connection->intf_cport_id = cport_id;
	connection->hd = hd;
	connection->intf = intf;
	connection->bundle = bundle;
	connection->handler = handler;
	connection->flags = flags;
	if (intf && (intf->quirks & GB_INTERFACE_QUIRK_NO_CPORT_FEATURES))
		connection->flags |= GB_CONNECTION_FLAG_NO_FLOWCTRL;
	connection->state = GB_CONNECTION_STATE_DISABLED;

	atomic_set(&connection->op_cycle, 0);
	mutex_init(&connection->mutex);
	spin_lock_init(&connection->lock);
	INIT_LIST_HEAD(&connection->operations);

	connection->wq = alloc_workqueue("%s:%d", WQ_UNBOUND, 1,
					 dev_name(&hd->dev), hd_cport_id);
	if (!connection->wq) {
		ret = -ENOMEM;
		goto err_free_connection;
	}

	kref_init(&connection->kref);

	gb_connection_init_name(connection);

	spin_lock_irq(&gb_connections_lock);
	list_add(&connection->hd_links, &hd->connections);

	if (bundle)
		list_add(&connection->bundle_links, &bundle->connections);
	else
		INIT_LIST_HEAD(&connection->bundle_links);

	spin_unlock_irq(&gb_connections_lock);

	mutex_unlock(&gb_connection_mutex);

	trace_gb_connection_create(connection);

	return connection;

err_free_connection:
	kfree(connection);
err_hd_cport_release:
	gb_hd_cport_release(hd, hd_cport_id);
err_unlock:
	mutex_unlock(&gb_connection_mutex);

	return ERR_PTR(ret);
}