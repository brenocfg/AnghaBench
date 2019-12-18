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
struct qedf_ioreq {int /*<<< orphan*/  timeout_work; } ;
struct qedf_ctx {int /*<<< orphan*/  timer_work_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void qedf_cmd_timer_set(struct qedf_ctx *qedf, struct qedf_ioreq *io_req,
	unsigned int timer_msec)
{
	queue_delayed_work(qedf->timer_work_queue, &io_req->timeout_work,
	    msecs_to_jiffies(timer_msec));
}