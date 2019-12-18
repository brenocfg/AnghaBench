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
struct gb_operation {int /*<<< orphan*/  id; } ;
struct gb_loopback_async_operation {int (* completion ) (struct gb_loopback_async_operation*) ;struct gb_loopback* gb; int /*<<< orphan*/  ts; } ;
struct gb_loopback {int /*<<< orphan*/  wq_completion; int /*<<< orphan*/  outstanding_operations; TYPE_2__* connection; int /*<<< orphan*/  mutex; int /*<<< orphan*/  iteration_count; int /*<<< orphan*/  requests_timedout; int /*<<< orphan*/  error; int /*<<< orphan*/  elapsed_nsecs; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_4__ {TYPE_1__* bundle; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_loopback_calc_latency (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_loopback_calculate_stats (struct gb_loopback*,int) ; 
 struct gb_loopback_async_operation* gb_operation_get_data (struct gb_operation*) ; 
 int /*<<< orphan*/  gb_operation_put (struct gb_operation*) ; 
 int gb_operation_result (struct gb_operation*) ; 
 int /*<<< orphan*/  kfree (struct gb_loopback_async_operation*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct gb_loopback_async_operation*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_loopback_async_operation_callback(struct gb_operation *operation)
{
	struct gb_loopback_async_operation *op_async;
	struct gb_loopback *gb;
	ktime_t te;
	int result;

	te = ktime_get();
	result = gb_operation_result(operation);
	op_async = gb_operation_get_data(operation);
	gb = op_async->gb;

	mutex_lock(&gb->mutex);

	if (!result && op_async->completion)
		result = op_async->completion(op_async);

	if (!result) {
		gb->elapsed_nsecs = gb_loopback_calc_latency(op_async->ts, te);
	} else {
		gb->error++;
		if (result == -ETIMEDOUT)
			gb->requests_timedout++;
	}

	gb->iteration_count++;
	gb_loopback_calculate_stats(gb, result);

	mutex_unlock(&gb->mutex);

	dev_dbg(&gb->connection->bundle->dev, "complete operation %d\n",
		operation->id);

	/* Wake up waiters */
	atomic_dec(&op_async->gb->outstanding_operations);
	wake_up(&gb->wq_completion);

	/* Release resources */
	gb_operation_put(operation);
	kfree(op_async);
}