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
struct gb_loopback {int /*<<< orphan*/  connection; int /*<<< orphan*/  id; int /*<<< orphan*/  dev; int /*<<< orphan*/  file; int /*<<< orphan*/  kfifo_lat; int /*<<< orphan*/  task; } ;
struct gb_bundle {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_latency_tag_disable (int /*<<< orphan*/ ) ; 
 TYPE_1__ gb_dev ; 
 int /*<<< orphan*/  gb_loopback_async_wait_all (struct gb_loopback*) ; 
 int /*<<< orphan*/  gb_pm_runtime_get_noresume (struct gb_bundle*) ; 
 int gb_pm_runtime_get_sync (struct gb_bundle*) ; 
 struct gb_loopback* greybus_get_drvdata (struct gb_bundle*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gb_loopback*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loopback_ida ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gb_loopback_disconnect(struct gb_bundle *bundle)
{
	struct gb_loopback *gb = greybus_get_drvdata(bundle);
	unsigned long flags;
	int ret;

	ret = gb_pm_runtime_get_sync(bundle);
	if (ret)
		gb_pm_runtime_get_noresume(bundle);

	gb_connection_disable(gb->connection);

	if (!IS_ERR_OR_NULL(gb->task))
		kthread_stop(gb->task);

	kfifo_free(&gb->kfifo_lat);
	gb_connection_latency_tag_disable(gb->connection);
	debugfs_remove(gb->file);

	/*
	 * FIXME: gb_loopback_async_wait_all() is redundant now, as connection
	 * is disabled at the beginning and so we can't have any more
	 * incoming/outgoing requests.
	 */
	gb_loopback_async_wait_all(gb);

	spin_lock_irqsave(&gb_dev.lock, flags);
	gb_dev.count--;
	spin_unlock_irqrestore(&gb_dev.lock, flags);

	device_unregister(gb->dev);
	ida_simple_remove(&loopback_ida, gb->id);

	gb_connection_destroy(gb->connection);
	kfree(gb);
}