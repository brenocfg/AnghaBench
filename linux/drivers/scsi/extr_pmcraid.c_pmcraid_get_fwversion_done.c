#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct pmcraid_instance {TYPE_3__* host; int /*<<< orphan*/  ioa_state; } ;
struct pmcraid_cmd {TYPE_2__* ioa_cb; struct pmcraid_instance* drv_inst; } ;
struct TYPE_6__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  ioasc; } ;
struct TYPE_5__ {TYPE_1__ ioasa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOA_STATE_IN_RESET_ALERT ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  pmcraid_querycfg (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  pmcraid_reset_alert (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void pmcraid_get_fwversion_done(struct pmcraid_cmd *cmd)
{
	struct pmcraid_instance *pinstance = cmd->drv_inst;
	u32 ioasc = le32_to_cpu(cmd->ioa_cb->ioasa.ioasc);
	unsigned long lock_flags;

	/* configuration table entry size depends on firmware version. If fw
	 * version is not known, it is not possible to interpret IOA config
	 * table
	 */
	if (ioasc) {
		pmcraid_err("IOA Inquiry failed with %x\n", ioasc);
		spin_lock_irqsave(pinstance->host->host_lock, lock_flags);
		pinstance->ioa_state = IOA_STATE_IN_RESET_ALERT;
		pmcraid_reset_alert(cmd);
		spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
	} else  {
		pmcraid_querycfg(cmd);
	}
}