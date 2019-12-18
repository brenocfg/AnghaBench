#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong ;
struct notifier_block {int dummy; } ;
struct TYPE_11__ {scalar_t__ reserved4; scalar_t__ reserved3; scalar_t__ reserved2; scalar_t__ reserved; int /*<<< orphan*/  state; int /*<<< orphan*/  command_id; void* op_code; } ;
struct TYPE_12__ {TYPE_1__ flush_cache; } ;
struct TYPE_13__ {TYPE_2__ cmd; void** cdb; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_3__ ips_scb_t ;
struct TYPE_14__ {int max_cmds; int /*<<< orphan*/  pcidev; TYPE_3__* scbs; int /*<<< orphan*/  active; } ;
typedef  TYPE_4__ ips_ha_t ;

/* Variables and functions */
 void* IPS_CMD_FLUSH ; 
 int /*<<< orphan*/  IPS_COMMAND_ID (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ IPS_FAILURE ; 
 int /*<<< orphan*/  IPS_INTR_ON ; 
 int /*<<< orphan*/  IPS_NORM_STATE ; 
 int /*<<< orphan*/  IPS_PRINTK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 scalar_t__ SYS_HALT ; 
 scalar_t__ SYS_POWER_OFF ; 
 scalar_t__ SYS_RESTART ; 
 int /*<<< orphan*/  ips_cmd_timeout ; 
 scalar_t__* ips_ha ; 
 int /*<<< orphan*/  ips_init_scb (TYPE_4__*,TYPE_3__*) ; 
 int ips_next_controller ; 
 scalar_t__ ips_send_wait (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ips_halt(struct notifier_block *nb, ulong event, void *buf)
{
	ips_scb_t *scb;
	ips_ha_t *ha;
	int i;

	if ((event != SYS_RESTART) && (event != SYS_HALT) &&
	    (event != SYS_POWER_OFF))
		return (NOTIFY_DONE);

	for (i = 0; i < ips_next_controller; i++) {
		ha = (ips_ha_t *) ips_ha[i];

		if (!ha)
			continue;

		if (!ha->active)
			continue;

		/* flush the cache on the controller */
		scb = &ha->scbs[ha->max_cmds - 1];

		ips_init_scb(ha, scb);

		scb->timeout = ips_cmd_timeout;
		scb->cdb[0] = IPS_CMD_FLUSH;

		scb->cmd.flush_cache.op_code = IPS_CMD_FLUSH;
		scb->cmd.flush_cache.command_id = IPS_COMMAND_ID(ha, scb);
		scb->cmd.flush_cache.state = IPS_NORM_STATE;
		scb->cmd.flush_cache.reserved = 0;
		scb->cmd.flush_cache.reserved2 = 0;
		scb->cmd.flush_cache.reserved3 = 0;
		scb->cmd.flush_cache.reserved4 = 0;

		IPS_PRINTK(KERN_WARNING, ha->pcidev, "Flushing Cache.\n");

		/* send command */
		if (ips_send_wait(ha, scb, ips_cmd_timeout, IPS_INTR_ON) ==
		    IPS_FAILURE)
			IPS_PRINTK(KERN_WARNING, ha->pcidev,
				   "Incomplete Flush.\n");
		else
			IPS_PRINTK(KERN_WARNING, ha->pcidev,
				   "Flushing Complete.\n");
	}

	return (NOTIFY_OK);
}