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
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ u32 ;
struct sym_hcb {int rv_ctest3; } ;
struct sym_ccb {int /*<<< orphan*/  host_status; } ;

/* Variables and functions */
 int CLF ; 
 int CSF ; 
 scalar_t__ INL (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTB (struct sym_hcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTL (struct sym_hcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTL_DSP (struct sym_hcb*,scalar_t__) ; 
 scalar_t__ SCRIPTA_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 scalar_t__ SCRIPTB_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int TE ; 
 int /*<<< orphan*/  complete_error ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  done_end ; 
 int /*<<< orphan*/  getjob_begin ; 
 int /*<<< orphan*/  getjob_end ; 
 int /*<<< orphan*/  nc_ctest3 ; 
 int /*<<< orphan*/  nc_dsa ; 
 int /*<<< orphan*/  nc_dsp ; 
 int /*<<< orphan*/  nc_stest3 ; 
 int /*<<< orphan*/  reselect ; 
 int /*<<< orphan*/  sel_for_abort ; 
 int /*<<< orphan*/  sel_for_abort_1 ; 
 int /*<<< orphan*/  start ; 
 struct sym_ccb* sym_ccb_from_dsa (struct sym_hcb*,scalar_t__) ; 
 int /*<<< orphan*/  sym_start_reset (struct sym_hcb*) ; 
 int /*<<< orphan*/  ungetjob ; 

__attribute__((used)) static void sym_recover_scsi_int (struct sym_hcb *np, u_char hsts)
{
	u32	dsp	= INL(np, nc_dsp);
	u32	dsa	= INL(np, nc_dsa);
	struct sym_ccb *cp	= sym_ccb_from_dsa(np, dsa);

	/*
	 *  If we haven't been interrupted inside the SCRIPTS 
	 *  critical pathes, we can safely restart the SCRIPTS 
	 *  and trust the DSA value if it matches a CCB.
	 */
	if ((!(dsp > SCRIPTA_BA(np, getjob_begin) &&
	       dsp < SCRIPTA_BA(np, getjob_end) + 1)) &&
	    (!(dsp > SCRIPTA_BA(np, ungetjob) &&
	       dsp < SCRIPTA_BA(np, reselect) + 1)) &&
	    (!(dsp > SCRIPTB_BA(np, sel_for_abort) &&
	       dsp < SCRIPTB_BA(np, sel_for_abort_1) + 1)) &&
	    (!(dsp > SCRIPTA_BA(np, done) &&
	       dsp < SCRIPTA_BA(np, done_end) + 1))) {
		OUTB(np, nc_ctest3, np->rv_ctest3 | CLF); /* clear dma fifo  */
		OUTB(np, nc_stest3, TE|CSF);		/* clear scsi fifo */
		/*
		 *  If we have a CCB, let the SCRIPTS call us back for 
		 *  the handling of the error with SCRATCHA filled with 
		 *  STARTPOS. This way, we will be able to freeze the 
		 *  device queue and requeue awaiting IOs.
		 */
		if (cp) {
			cp->host_status = hsts;
			OUTL_DSP(np, SCRIPTA_BA(np, complete_error));
		}
		/*
		 *  Otherwise just restart the SCRIPTS.
		 */
		else {
			OUTL(np, nc_dsa, 0xffffff);
			OUTL_DSP(np, SCRIPTA_BA(np, start));
		}
	}
	else
		goto reset_all;

	return;

reset_all:
	sym_start_reset(np);
}