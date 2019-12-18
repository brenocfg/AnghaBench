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
struct timer_list {int dummy; } ;
struct ipr_ioa_cfg {scalar_t__ sdt_state; TYPE_2__* host; int /*<<< orphan*/  reset_retries; struct ipr_cmnd* reset_cmd; int /*<<< orphan*/  in_reset_reload; TYPE_1__* pdev; int /*<<< orphan*/  errors_logged; } ;
struct ipr_cmnd {struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 scalar_t__ GET_DUMP ; 
 scalar_t__ IPR_NUM_RESET_RELOAD_RETRIES ; 
 int /*<<< orphan*/  IPR_SHUTDOWN_NONE ; 
 int /*<<< orphan*/  LEAVE ; 
 scalar_t__ WAIT_FOR_DUMP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ipr_cmnd* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ipr_cmnd* ipr_cmd ; 
 scalar_t__ ipr_fastfail ; 
 int /*<<< orphan*/  ipr_initiate_ioa_reset (struct ipr_ioa_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void ipr_oper_timeout(struct timer_list *t)
{
	struct ipr_cmnd *ipr_cmd = from_timer(ipr_cmd, t, timer);
	unsigned long lock_flags = 0;
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);

	ioa_cfg->errors_logged++;
	dev_err(&ioa_cfg->pdev->dev,
		"Adapter timed out transitioning to operational.\n");

	if (WAIT_FOR_DUMP == ioa_cfg->sdt_state)
		ioa_cfg->sdt_state = GET_DUMP;

	if (!ioa_cfg->in_reset_reload || ioa_cfg->reset_cmd == ipr_cmd) {
		if (ipr_fastfail)
			ioa_cfg->reset_retries += IPR_NUM_RESET_RELOAD_RETRIES;
		ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);
	}

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	LEAVE;
}