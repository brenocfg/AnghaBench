#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_12__ {TYPE_3__* host; } ;
struct TYPE_11__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_10__ {TYPE_1__* host; } ;
struct TYPE_9__ {scalar_t__ hostdata; } ;
typedef  TYPE_4__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_NOP ; 
 int /*<<< orphan*/  CMD_RESETCHIP ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int SUCCESS ; 
 int /*<<< orphan*/  fas216_checkmagic (TYPE_4__*) ; 
 int /*<<< orphan*/  fas216_cmd (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fas216_init_chip (TYPE_4__*) ; 
 int /*<<< orphan*/  fas216_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

int fas216_eh_host_reset(struct scsi_cmnd *SCpnt)
{
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;

	spin_lock_irq(info->host->host_lock);

	fas216_checkmagic(info);

	fas216_log(info, LOG_ERROR, "resetting host");

	/*
	 * Reset the SCSI chip.
	 */
	fas216_cmd(info, CMD_RESETCHIP);

	/*
	 * Ugly ugly ugly!
	 * We need to release the host_lock and enable
	 * IRQs if we sleep, but we must relock and disable
	 * IRQs after the sleep.
	 */
	spin_unlock_irq(info->host->host_lock);
	msleep(50 * 1000/100);
	spin_lock_irq(info->host->host_lock);

	/*
	 * Release the SCSI reset.
	 */
	fas216_cmd(info, CMD_NOP);

	fas216_init_chip(info);

	spin_unlock_irq(info->host->host_lock);
	return SUCCESS;
}