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
struct spi_controller {int /*<<< orphan*/  kworker_task; int /*<<< orphan*/  dev; } ;
struct sched_param {int sched_priority; } ;

/* Variables and functions */
 int MAX_RT_PRIO ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 

__attribute__((used)) static void spi_set_thread_rt(struct spi_controller *ctlr)
{
	struct sched_param param = { .sched_priority = MAX_RT_PRIO / 2 };

	dev_info(&ctlr->dev,
		"will run message pump with realtime priority\n");
	sched_setscheduler(ctlr->kworker_task, SCHED_FIFO, &param);
}