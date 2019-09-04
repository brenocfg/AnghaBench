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
struct crypto_engine {int running; int /*<<< orphan*/  pump_requests; int /*<<< orphan*/  kworker; int /*<<< orphan*/  queue_lock; scalar_t__ busy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  kthread_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int crypto_engine_start(struct crypto_engine *engine)
{
	unsigned long flags;

	spin_lock_irqsave(&engine->queue_lock, flags);

	if (engine->running || engine->busy) {
		spin_unlock_irqrestore(&engine->queue_lock, flags);
		return -EBUSY;
	}

	engine->running = true;
	spin_unlock_irqrestore(&engine->queue_lock, flags);

	kthread_queue_work(engine->kworker, &engine->pump_requests);

	return 0;
}