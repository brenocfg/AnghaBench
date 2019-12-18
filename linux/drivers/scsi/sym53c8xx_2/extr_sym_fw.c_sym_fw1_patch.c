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
struct sym_hcb {int features; int /*<<< orphan*/  targtbl_ba; int /*<<< orphan*/  dqueue_ba; int /*<<< orphan*/  squeue_ba; scalar_t__ scriptb0; scalar_t__ scripta0; } ;
struct sym_fw1b_scr {void** targtbl; void** done_pos; void** startpos; } ;
struct sym_fw1a_scr {void** ungetjob; void** start; void** reselected; void** idle; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int FE_LED0 ; 
 int /*<<< orphan*/  SCR_NO_OP ; 
 int /*<<< orphan*/  SYM_CONF_SET_IARB_ON_ARB_LOST ; 
 void* cpu_to_scr (int /*<<< orphan*/ ) ; 
 struct sym_hcb* sym_get_hcb (struct Scsi_Host*) ; 

__attribute__((used)) static void
sym_fw1_patch(struct Scsi_Host *shost)
{
	struct sym_hcb *np = sym_get_hcb(shost);
	struct sym_fw1a_scr *scripta0;
	struct sym_fw1b_scr *scriptb0;

	scripta0 = (struct sym_fw1a_scr *) np->scripta0;
	scriptb0 = (struct sym_fw1b_scr *) np->scriptb0;

	/*
	 *  Remove LED support if not needed.
	 */
	if (!(np->features & FE_LED0)) {
		scripta0->idle[0]	= cpu_to_scr(SCR_NO_OP);
		scripta0->reselected[0]	= cpu_to_scr(SCR_NO_OP);
		scripta0->start[0]	= cpu_to_scr(SCR_NO_OP);
	}

#ifdef SYM_CONF_IARB_SUPPORT
	/*
	 *    If user does not want to use IMMEDIATE ARBITRATION
	 *    when we are reselected while attempting to arbitrate,
	 *    patch the SCRIPTS accordingly with a SCRIPT NO_OP.
	 */
	if (!SYM_CONF_SET_IARB_ON_ARB_LOST)
		scripta0->ungetjob[0] = cpu_to_scr(SCR_NO_OP);
#endif
	/*
	 *  Patch some data in SCRIPTS.
	 *  - start and done queue initial bus address.
	 *  - target bus address table bus address.
	 */
	scriptb0->startpos[0]	= cpu_to_scr(np->squeue_ba);
	scriptb0->done_pos[0]	= cpu_to_scr(np->dqueue_ba);
	scriptb0->targtbl[0]	= cpu_to_scr(np->targtbl_ba);
}