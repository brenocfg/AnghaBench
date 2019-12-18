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
typedef  int u_short ;
struct sym_hcb {scalar_t__ iarb_count; scalar_t__ iarb_max; int squeueput; int istat_sem; void** squeue; int /*<<< orphan*/  idletask_ba; scalar_t__ dmap_dirty; struct sym_ccb* last_cp; } ;
struct sym_ccb {int /*<<< orphan*/  cmd; int /*<<< orphan*/  ccb_ba; int /*<<< orphan*/  host_xflags; int /*<<< orphan*/  host_flags; } ;

/* Variables and functions */
 int DEBUG_FLAGS ; 
 int DEBUG_QUEUE ; 
 int /*<<< orphan*/  HF_HINT_IARB ; 
 int /*<<< orphan*/  HX_DMAP_DIRTY ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int MAX_QUEUE ; 
 int /*<<< orphan*/  MEMORY_WRITE_BARRIER () ; 
 int /*<<< orphan*/  OUTB (struct sym_hcb*,int /*<<< orphan*/ ,int) ; 
 int SIGP ; 
 void* cpu_to_scr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nc_istat ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

void sym_put_start_queue(struct sym_hcb *np, struct sym_ccb *cp)
{
	u_short	qidx;

#ifdef SYM_CONF_IARB_SUPPORT
	/*
	 *  If the previously queued CCB is not yet done, 
	 *  set the IARB hint. The SCRIPTS will go with IARB 
	 *  for this job when starting the previous one.
	 *  We leave devices a chance to win arbitration by 
	 *  not using more than 'iarb_max' consecutive 
	 *  immediate arbitrations.
	 */
	if (np->last_cp && np->iarb_count < np->iarb_max) {
		np->last_cp->host_flags |= HF_HINT_IARB;
		++np->iarb_count;
	}
	else
		np->iarb_count = 0;
	np->last_cp = cp;
#endif

#if   SYM_CONF_DMA_ADDRESSING_MODE == 2
	/*
	 *  Make SCRIPTS aware of the 64 bit DMA 
	 *  segment registers not being up-to-date.
	 */
	if (np->dmap_dirty)
		cp->host_xflags |= HX_DMAP_DIRTY;
#endif

	/*
	 *  Insert first the idle task and then our job.
	 *  The MBs should ensure proper ordering.
	 */
	qidx = np->squeueput + 2;
	if (qidx >= MAX_QUEUE*2) qidx = 0;

	np->squeue [qidx]	   = cpu_to_scr(np->idletask_ba);
	MEMORY_WRITE_BARRIER();
	np->squeue [np->squeueput] = cpu_to_scr(cp->ccb_ba);

	np->squeueput = qidx;

	if (DEBUG_FLAGS & DEBUG_QUEUE)
		scmd_printk(KERN_DEBUG, cp->cmd, "queuepos=%d\n",
							np->squeueput);

	/*
	 *  Script processor may be waiting for reselect.
	 *  Wake it up.
	 */
	MEMORY_WRITE_BARRIER();
	OUTB(np, nc_istat, SIGP|np->istat_sem);
}