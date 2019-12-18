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
struct scsi_ctrl_blk {int next_state; size_t target; int /*<<< orphan*/  status; } ;
struct initio_host {scalar_t__ addr; int /*<<< orphan*/ * targets; int /*<<< orphan*/ * active_tc; struct scsi_ctrl_blk* active; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCB_SELECT ; 
 int /*<<< orphan*/  TSC_SELATNSTOP ; 
 scalar_t__ TUL_SCmd ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void initio_select_atn_stop(struct initio_host * host, struct scsi_ctrl_blk * scb)
{
	scb->status |= SCB_SELECT;
	scb->next_state = 0x1;
	host->active = scb;
	host->active_tc = &host->targets[scb->target];
	outb(TSC_SELATNSTOP, host->addr + TUL_SCmd);
}