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
struct spi_controller {int running; int busy; scalar_t__ rt; int /*<<< orphan*/  pump_messages; int /*<<< orphan*/  kworker_task; int /*<<< orphan*/  dev; int /*<<< orphan*/  kworker; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_init_worker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_worker_fn ; 
 int /*<<< orphan*/  spi_pump_messages ; 
 int /*<<< orphan*/  spi_set_thread_rt (struct spi_controller*) ; 

__attribute__((used)) static int spi_init_queue(struct spi_controller *ctlr)
{
	ctlr->running = false;
	ctlr->busy = false;

	kthread_init_worker(&ctlr->kworker);
	ctlr->kworker_task = kthread_run(kthread_worker_fn, &ctlr->kworker,
					 "%s", dev_name(&ctlr->dev));
	if (IS_ERR(ctlr->kworker_task)) {
		dev_err(&ctlr->dev, "failed to create message pump task\n");
		return PTR_ERR(ctlr->kworker_task);
	}
	kthread_init_work(&ctlr->pump_messages, spi_pump_messages);

	/*
	 * Controller config will indicate if this controller should run the
	 * message pump with high (realtime) priority to reduce the transfer
	 * latency on the bus by minimising the delay between a transfer
	 * request and the scheduling of the message pump thread. Without this
	 * setting the message pump thread will remain at default priority.
	 */
	if (ctlr->rt)
		spi_set_thread_rt(ctlr);

	return 0;
}