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
typedef  int /*<<< orphan*/  u32 ;
struct greybus_descriptor_cport {scalar_t__ protocol_id; int /*<<< orphan*/  id; } ;
struct greybus_bundle_id {int dummy; } ;
struct gb_loopback_transfer_request {int dummy; } ;
struct gb_loopback {int id; int /*<<< orphan*/  file; int /*<<< orphan*/  kfifo_lat; struct gb_connection* task; int /*<<< orphan*/  mutex; struct gb_connection* dev; void* timeout_max; void* timeout_min; int /*<<< orphan*/  outstanding_operations; int /*<<< orphan*/  wq_completion; int /*<<< orphan*/  wq; struct gb_connection* connection; } ;
struct gb_connection {TYPE_1__* bundle; } ;
struct gb_bundle {int num_cports; struct greybus_descriptor_cport* cport_desc; } ;
struct device {TYPE_1__* bundle; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {int size_max; int /*<<< orphan*/  lock; int /*<<< orphan*/  count; int /*<<< orphan*/  root; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DEBUGFS_NAMELEN ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GB_LOOPBACK_TIMEOUT_MAX ; 
 int /*<<< orphan*/  GB_LOOPBACK_TIMEOUT_MIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GREYBUS_PROTOCOL_LOOPBACK ; 
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct gb_connection*) ; 
 int S_IFREG ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct gb_loopback*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 struct gb_connection* device_create_with_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gb_loopback*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_unregister (struct gb_connection*) ; 
 struct gb_connection* gb_connection_create (struct gb_bundle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_latency_tag_enable (struct gb_connection*) ; 
 TYPE_2__ gb_dev ; 
 int /*<<< orphan*/  gb_loopback_dbgfs_latency_fops ; 
 int /*<<< orphan*/  gb_loopback_fn ; 
 int /*<<< orphan*/  gb_loopback_request_handler ; 
 int /*<<< orphan*/  gb_loopback_reset_stats (struct gb_loopback*) ; 
 int gb_operation_get_payload_size_max (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (struct gb_bundle*) ; 
 int /*<<< orphan*/  greybus_set_drvdata (struct gb_bundle*,struct gb_loopback*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 void* jiffies_to_usecs (int /*<<< orphan*/ ) ; 
 scalar_t__ kfifo_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int kfifo_depth ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gb_loopback*) ; 
 struct gb_connection* kthread_run (int /*<<< orphan*/ ,struct gb_loopback*,char*) ; 
 struct gb_loopback* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loopback_class ; 
 int /*<<< orphan*/  loopback_groups ; 
 int /*<<< orphan*/  loopback_ida ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int gb_loopback_probe(struct gb_bundle *bundle,
			     const struct greybus_bundle_id *id)
{
	struct greybus_descriptor_cport *cport_desc;
	struct gb_connection *connection;
	struct gb_loopback *gb;
	struct device *dev;
	int retval;
	char name[DEBUGFS_NAMELEN];
	unsigned long flags;

	if (bundle->num_cports != 1)
		return -ENODEV;

	cport_desc = &bundle->cport_desc[0];
	if (cport_desc->protocol_id != GREYBUS_PROTOCOL_LOOPBACK)
		return -ENODEV;

	gb = kzalloc(sizeof(*gb), GFP_KERNEL);
	if (!gb)
		return -ENOMEM;

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  gb_loopback_request_handler);
	if (IS_ERR(connection)) {
		retval = PTR_ERR(connection);
		goto out_kzalloc;
	}

	gb->connection = connection;
	greybus_set_drvdata(bundle, gb);

	init_waitqueue_head(&gb->wq);
	init_waitqueue_head(&gb->wq_completion);
	atomic_set(&gb->outstanding_operations, 0);
	gb_loopback_reset_stats(gb);

	/* Reported values to user-space for min/max timeouts */
	gb->timeout_min = jiffies_to_usecs(GB_LOOPBACK_TIMEOUT_MIN);
	gb->timeout_max = jiffies_to_usecs(GB_LOOPBACK_TIMEOUT_MAX);

	if (!gb_dev.count) {
		/* Calculate maximum payload */
		gb_dev.size_max = gb_operation_get_payload_size_max(connection);
		if (gb_dev.size_max <=
			sizeof(struct gb_loopback_transfer_request)) {
			retval = -EINVAL;
			goto out_connection_destroy;
		}
		gb_dev.size_max -= sizeof(struct gb_loopback_transfer_request);
	}

	/* Create per-connection sysfs and debugfs data-points */
	snprintf(name, sizeof(name), "raw_latency_%s",
		 dev_name(&connection->bundle->dev));
	gb->file = debugfs_create_file(name, S_IFREG | 0444, gb_dev.root, gb,
				       &gb_loopback_dbgfs_latency_fops);

	gb->id = ida_simple_get(&loopback_ida, 0, 0, GFP_KERNEL);
	if (gb->id < 0) {
		retval = gb->id;
		goto out_debugfs_remove;
	}

	retval = gb_connection_enable(connection);
	if (retval)
		goto out_ida_remove;

	dev = device_create_with_groups(&loopback_class,
					&connection->bundle->dev,
					MKDEV(0, 0), gb, loopback_groups,
					"gb_loopback%d", gb->id);
	if (IS_ERR(dev)) {
		retval = PTR_ERR(dev);
		goto out_connection_disable;
	}
	gb->dev = dev;

	/* Allocate kfifo */
	if (kfifo_alloc(&gb->kfifo_lat, kfifo_depth * sizeof(u32),
			GFP_KERNEL)) {
		retval = -ENOMEM;
		goto out_conn;
	}
	/* Fork worker thread */
	mutex_init(&gb->mutex);
	gb->task = kthread_run(gb_loopback_fn, gb, "gb_loopback");
	if (IS_ERR(gb->task)) {
		retval = PTR_ERR(gb->task);
		goto out_kfifo;
	}

	spin_lock_irqsave(&gb_dev.lock, flags);
	gb_dev.count++;
	spin_unlock_irqrestore(&gb_dev.lock, flags);

	gb_connection_latency_tag_enable(connection);

	gb_pm_runtime_put_autosuspend(bundle);

	return 0;

out_kfifo:
	kfifo_free(&gb->kfifo_lat);
out_conn:
	device_unregister(dev);
out_connection_disable:
	gb_connection_disable(connection);
out_ida_remove:
	ida_simple_remove(&loopback_ida, gb->id);
out_debugfs_remove:
	debugfs_remove(gb->file);
out_connection_destroy:
	gb_connection_destroy(connection);
out_kzalloc:
	kfree(gb);

	return retval;
}