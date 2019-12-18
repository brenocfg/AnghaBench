#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_3__* device; } ;
struct TYPE_13__ {int /*<<< orphan*/  opcode; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_4__ megacmd_t ;
struct TYPE_14__ {int /*<<< orphan*/  lock; TYPE_1__* dev; } ;
typedef  TYPE_5__ adapter_t ;
struct TYPE_12__ {TYPE_2__* host; } ;
struct TYPE_11__ {scalar_t__ hostdata; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEGA_CLUSTER_CMD ; 
 int /*<<< orphan*/  MEGA_RESET_RESERVATIONS ; 
 int /*<<< orphan*/  SCB_RESET ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mega_internal_command (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mega_rundoneq (TYPE_5__*) ; 
 int megaraid_abort_and_reset (TYPE_5__*,struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
megaraid_reset(struct scsi_cmnd *cmd)
{
	adapter_t	*adapter;
	megacmd_t	mc;
	int		rval;

	adapter = (adapter_t *)cmd->device->host->hostdata;

#if MEGA_HAVE_CLUSTERING
	mc.cmd = MEGA_CLUSTER_CMD;
	mc.opcode = MEGA_RESET_RESERVATIONS;

	if( mega_internal_command(adapter, &mc, NULL) != 0 ) {
		dev_warn(&adapter->dev->dev, "reservation reset failed\n");
	}
	else {
		dev_info(&adapter->dev->dev, "reservation reset\n");
	}
#endif

	spin_lock_irq(&adapter->lock);

	rval =  megaraid_abort_and_reset(adapter, cmd, SCB_RESET);

	/*
	 * This is required here to complete any completed requests
	 * to be communicated over to the mid layer.
	 */
	mega_rundoneq(adapter);
	spin_unlock_irq(&adapter->lock);

	return rval;
}