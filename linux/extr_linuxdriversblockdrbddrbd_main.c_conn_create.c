#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct res_opts {int dummy; } ;
struct drbd_resource {int /*<<< orphan*/  resources; int /*<<< orphan*/  connections; int /*<<< orphan*/  kref; } ;
struct drbd_epoch {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {struct drbd_connection* connection; } ;
struct TYPE_5__ {int seen_any_write_yet; scalar_t__ current_epoch_writes; scalar_t__ current_epoch_nr; } ;
struct drbd_connection {int epochs; TYPE_3__ data; TYPE_3__ meta; struct drbd_connection* current_epoch; int /*<<< orphan*/  connections; struct drbd_resource* resource; int /*<<< orphan*/  kref; TYPE_2__ ack_receiver; TYPE_2__ worker; TYPE_2__ receiver; int /*<<< orphan*/  sender_work; int /*<<< orphan*/  peer_devices; int /*<<< orphan*/  ping_wait; int /*<<< orphan*/  cstate_mutex; int /*<<< orphan*/  cstate; TYPE_1__ send; int /*<<< orphan*/  epoch_lock; int /*<<< orphan*/  list; int /*<<< orphan*/  transfer_log; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_STANDALONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_ack_receiver ; 
 scalar_t__ drbd_alloc_socket (TYPE_3__*) ; 
 struct drbd_resource* drbd_create_resource (char const*) ; 
 int /*<<< orphan*/  drbd_debugfs_connection_add (struct drbd_connection*) ; 
 int /*<<< orphan*/  drbd_free_resource (struct drbd_resource*) ; 
 int /*<<< orphan*/  drbd_free_socket (TYPE_3__*) ; 
 int /*<<< orphan*/  drbd_init_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_receiver ; 
 int /*<<< orphan*/  drbd_thread_init (struct drbd_resource*,TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drbd_worker ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drbd_connection*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ set_resource_options (struct drbd_resource*,struct res_opts*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct drbd_connection *conn_create(const char *name, struct res_opts *res_opts)
{
	struct drbd_resource *resource;
	struct drbd_connection *connection;

	connection = kzalloc(sizeof(struct drbd_connection), GFP_KERNEL);
	if (!connection)
		return NULL;

	if (drbd_alloc_socket(&connection->data))
		goto fail;
	if (drbd_alloc_socket(&connection->meta))
		goto fail;

	connection->current_epoch = kzalloc(sizeof(struct drbd_epoch), GFP_KERNEL);
	if (!connection->current_epoch)
		goto fail;

	INIT_LIST_HEAD(&connection->transfer_log);

	INIT_LIST_HEAD(&connection->current_epoch->list);
	connection->epochs = 1;
	spin_lock_init(&connection->epoch_lock);

	connection->send.seen_any_write_yet = false;
	connection->send.current_epoch_nr = 0;
	connection->send.current_epoch_writes = 0;

	resource = drbd_create_resource(name);
	if (!resource)
		goto fail;

	connection->cstate = C_STANDALONE;
	mutex_init(&connection->cstate_mutex);
	init_waitqueue_head(&connection->ping_wait);
	idr_init(&connection->peer_devices);

	drbd_init_workqueue(&connection->sender_work);
	mutex_init(&connection->data.mutex);
	mutex_init(&connection->meta.mutex);

	drbd_thread_init(resource, &connection->receiver, drbd_receiver, "receiver");
	connection->receiver.connection = connection;
	drbd_thread_init(resource, &connection->worker, drbd_worker, "worker");
	connection->worker.connection = connection;
	drbd_thread_init(resource, &connection->ack_receiver, drbd_ack_receiver, "ack_recv");
	connection->ack_receiver.connection = connection;

	kref_init(&connection->kref);

	connection->resource = resource;

	if (set_resource_options(resource, res_opts))
		goto fail_resource;

	kref_get(&resource->kref);
	list_add_tail_rcu(&connection->connections, &resource->connections);
	drbd_debugfs_connection_add(connection);
	return connection;

fail_resource:
	list_del(&resource->resources);
	drbd_free_resource(resource);
fail:
	kfree(connection->current_epoch);
	drbd_free_socket(&connection->meta);
	drbd_free_socket(&connection->data);
	kfree(connection);
	return NULL;
}