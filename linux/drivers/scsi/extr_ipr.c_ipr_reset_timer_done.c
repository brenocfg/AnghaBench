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
struct timer_list {int dummy; } ;
struct ipr_ioa_cfg {TYPE_1__* host; struct ipr_cmnd* reset_cmd; } ;
struct ipr_cmnd {int /*<<< orphan*/  (* done ) (struct ipr_cmnd*) ;int /*<<< orphan*/  queue; struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 struct ipr_cmnd* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ipr_cmnd* ipr_cmd ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ipr_cmnd*) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void ipr_reset_timer_done(struct timer_list *t)
{
	struct ipr_cmnd *ipr_cmd = from_timer(ipr_cmd, t, timer);
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	unsigned long lock_flags = 0;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);

	if (ioa_cfg->reset_cmd == ipr_cmd) {
		list_del(&ipr_cmd->queue);
		ipr_cmd->done(ipr_cmd);
	}

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
}