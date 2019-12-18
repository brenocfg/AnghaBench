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
struct gb_loopback {int type; scalar_t__ send_count; scalar_t__ iteration_max; scalar_t__ iteration_count; int us_wait; int /*<<< orphan*/  mutex; int /*<<< orphan*/  error; scalar_t__ async; int /*<<< orphan*/  ts; int /*<<< orphan*/  size; TYPE_2__* dev; int /*<<< orphan*/  wq; TYPE_1__* connection; } ;
struct gb_bundle {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {struct gb_bundle* bundle; } ;

/* Variables and functions */
 int GB_LOOPBACK_TYPE_PING ; 
 int GB_LOOPBACK_TYPE_SINK ; 
 int GB_LOOPBACK_TYPE_TRANSFER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int gb_loopback_async_ping (struct gb_loopback*) ; 
 int gb_loopback_async_sink (struct gb_loopback*,int /*<<< orphan*/ ) ; 
 int gb_loopback_async_transfer (struct gb_loopback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_loopback_async_wait_all (struct gb_loopback*) ; 
 int /*<<< orphan*/  gb_loopback_async_wait_to_send (struct gb_loopback*) ; 
 int /*<<< orphan*/  gb_loopback_calculate_stats (struct gb_loopback*,int) ; 
 int gb_loopback_sync_ping (struct gb_loopback*) ; 
 int gb_loopback_sync_sink (struct gb_loopback*,int /*<<< orphan*/ ) ; 
 int gb_loopback_sync_transfer (struct gb_loopback*,int /*<<< orphan*/ ) ; 
 int gb_pm_runtime_get_sync (struct gb_bundle*) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (struct gb_bundle*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gb_loopback_fn(void *data)
{
	int error = 0;
	int us_wait = 0;
	int type;
	int ret;
	u32 size;

	struct gb_loopback *gb = data;
	struct gb_bundle *bundle = gb->connection->bundle;

	ret = gb_pm_runtime_get_sync(bundle);
	if (ret)
		return ret;

	while (1) {
		if (!gb->type) {
			gb_pm_runtime_put_autosuspend(bundle);
			wait_event_interruptible(gb->wq, gb->type ||
						 kthread_should_stop());
			ret = gb_pm_runtime_get_sync(bundle);
			if (ret)
				return ret;
		}

		if (kthread_should_stop())
			break;

		/* Limit the maximum number of in-flight async operations */
		gb_loopback_async_wait_to_send(gb);
		if (kthread_should_stop())
			break;

		mutex_lock(&gb->mutex);

		/* Optionally terminate */
		if (gb->send_count == gb->iteration_max) {
			mutex_unlock(&gb->mutex);

			/* Wait for synchronous and asynchronus completion */
			gb_loopback_async_wait_all(gb);

			/* Mark complete unless user-space has poked us */
			mutex_lock(&gb->mutex);
			if (gb->iteration_count == gb->iteration_max) {
				gb->type = 0;
				gb->send_count = 0;
				sysfs_notify(&gb->dev->kobj,  NULL,
					     "iteration_count");
				dev_dbg(&bundle->dev, "load test complete\n");
			} else {
				dev_dbg(&bundle->dev,
					"continuing on with new test set\n");
			}
			mutex_unlock(&gb->mutex);
			continue;
		}
		size = gb->size;
		us_wait = gb->us_wait;
		type = gb->type;
		if (ktime_to_ns(gb->ts) == 0)
			gb->ts = ktime_get();

		/* Else operations to perform */
		if (gb->async) {
			if (type == GB_LOOPBACK_TYPE_PING)
				error = gb_loopback_async_ping(gb);
			else if (type == GB_LOOPBACK_TYPE_TRANSFER)
				error = gb_loopback_async_transfer(gb, size);
			else if (type == GB_LOOPBACK_TYPE_SINK)
				error = gb_loopback_async_sink(gb, size);

			if (error) {
				gb->error++;
				gb->iteration_count++;
			}
		} else {
			/* We are effectively single threaded here */
			if (type == GB_LOOPBACK_TYPE_PING)
				error = gb_loopback_sync_ping(gb);
			else if (type == GB_LOOPBACK_TYPE_TRANSFER)
				error = gb_loopback_sync_transfer(gb, size);
			else if (type == GB_LOOPBACK_TYPE_SINK)
				error = gb_loopback_sync_sink(gb, size);

			if (error)
				gb->error++;
			gb->iteration_count++;
			gb_loopback_calculate_stats(gb, !!error);
		}
		gb->send_count++;
		mutex_unlock(&gb->mutex);

		if (us_wait) {
			if (us_wait < 20000)
				usleep_range(us_wait, us_wait + 100);
			else
				msleep(us_wait / 1000);
		}
	}

	gb_pm_runtime_put_autosuspend(bundle);

	return 0;
}