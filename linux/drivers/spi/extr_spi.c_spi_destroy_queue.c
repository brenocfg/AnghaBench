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
struct spi_controller {int /*<<< orphan*/  kworker_task; int /*<<< orphan*/  kworker; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kthread_flush_worker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int spi_stop_queue (struct spi_controller*) ; 

__attribute__((used)) static int spi_destroy_queue(struct spi_controller *ctlr)
{
	int ret;

	ret = spi_stop_queue(ctlr);

	/*
	 * kthread_flush_worker will block until all work is done.
	 * If the reason that stop_queue timed out is that the work will never
	 * finish, then it does no good to call flush/stop thread, so
	 * return anyway.
	 */
	if (ret) {
		dev_err(&ctlr->dev, "problem destroying queue\n");
		return ret;
	}

	kthread_flush_worker(&ctlr->kworker);
	kthread_stop(ctlr->kworker_task);

	return 0;
}