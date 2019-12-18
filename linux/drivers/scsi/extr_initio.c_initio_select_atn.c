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
struct scsi_ctrl_blk {int next_state; size_t target; int /*<<< orphan*/ * cdb; scalar_t__ cdblen; int /*<<< orphan*/  ident; int /*<<< orphan*/  status; } ;
struct initio_host {scalar_t__ addr; struct scsi_ctrl_blk* active; int /*<<< orphan*/ * targets; int /*<<< orphan*/ * active_tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCB_SELECT ; 
 int /*<<< orphan*/  TSC_SEL_ATN ; 
 scalar_t__ TUL_SCmd ; 
 scalar_t__ TUL_SFifo ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void initio_select_atn(struct initio_host * host, struct scsi_ctrl_blk * scb)
{
	int i;

	scb->status |= SCB_SELECT;
	scb->next_state = 0x2;

	outb(scb->ident, host->addr + TUL_SFifo);
	for (i = 0; i < (int) scb->cdblen; i++)
		outb(scb->cdb[i], host->addr + TUL_SFifo);
	host->active_tc = &host->targets[scb->target];
	host->active = scb;
	outb(TSC_SEL_ATN, host->addr + TUL_SCmd);
}