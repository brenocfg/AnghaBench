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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {void (* function ) (struct timer_list*) ;scalar_t__ expires; } ;
struct ipr_cmnd {void (* done ) (struct ipr_cmnd*) ;TYPE_2__ timer; TYPE_1__* hrrq; int /*<<< orphan*/  queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  hrrq_pending_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPR_TRACE_START ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ipr_send_command (struct ipr_cmnd*) ; 
 int /*<<< orphan*/  ipr_trc_hook (struct ipr_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipr_do_req(struct ipr_cmnd *ipr_cmd,
		       void (*done) (struct ipr_cmnd *),
		       void (*timeout_func) (struct timer_list *), u32 timeout)
{
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_pending_q);

	ipr_cmd->done = done;

	ipr_cmd->timer.expires = jiffies + timeout;
	ipr_cmd->timer.function = timeout_func;

	add_timer(&ipr_cmd->timer);

	ipr_trc_hook(ipr_cmd, IPR_TRACE_START, 0);

	ipr_send_command(ipr_cmd);
}