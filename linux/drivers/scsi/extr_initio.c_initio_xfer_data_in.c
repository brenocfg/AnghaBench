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
typedef  int u32 ;
struct scsi_ctrl_blk {int flags; int buflen; int bufptr; int next_state; scalar_t__ sglen; } ;
struct initio_host {scalar_t__ addr; struct scsi_ctrl_blk* active; } ;

/* Variables and functions */
 int SCF_DIR ; 
 int SCF_DOUT ; 
 int SCF_SG ; 
 int /*<<< orphan*/  TAX_SG_IN ; 
 int /*<<< orphan*/  TAX_X_IN ; 
 int /*<<< orphan*/  TSC_XF_DMA_IN ; 
 scalar_t__ TUL_SCmd ; 
 scalar_t__ TUL_SCnt0 ; 
 scalar_t__ TUL_XAddH ; 
 scalar_t__ TUL_XCmd ; 
 scalar_t__ TUL_XCntH ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static int initio_xfer_data_in(struct initio_host * host)
{
	struct scsi_ctrl_blk *scb = host->active;

	if ((scb->flags & SCF_DIR) == SCF_DOUT)
		return 6;	/* wrong direction */

	outl(scb->buflen, host->addr + TUL_SCnt0);
	outb(TSC_XF_DMA_IN, host->addr + TUL_SCmd);	/* 7/25/95 */

	if (scb->flags & SCF_SG) {	/* S/G xfer */
		outl(((u32) scb->sglen) << 3, host->addr + TUL_XCntH);
		outl(scb->bufptr, host->addr + TUL_XAddH);
		outb(TAX_SG_IN, host->addr + TUL_XCmd);
	} else {
		outl(scb->buflen, host->addr + TUL_XCntH);
		outl(scb->bufptr, host->addr + TUL_XAddH);
		outb(TAX_X_IN, host->addr + TUL_XCmd);
	}
	scb->next_state = 0x5;
	return 0;		/* return to OS, wait xfer done , let jas_isr come in */
}