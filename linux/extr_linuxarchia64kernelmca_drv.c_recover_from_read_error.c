#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ia64_sal_os_state {TYPE_2__* pal_min_state; } ;
struct ia64_psr {scalar_t__ cpl; int bn; scalar_t__ i; scalar_t__ ri; } ;
typedef  int /*<<< orphan*/  slidx_table_t ;
typedef  int /*<<< orphan*/  peidx_table_t ;
struct TYPE_7__ {scalar_t__ pmsa_iip; scalar_t__ pmsa_ipsr; scalar_t__* pmsa_gr; scalar_t__ pmsa_br0; } ;
typedef  TYPE_2__ pal_min_state_area_t ;
typedef  int /*<<< orphan*/  pal_bus_check_info_t ;
struct TYPE_8__ {scalar_t__ gp; scalar_t__ fp; } ;
typedef  TYPE_3__ ia64_fptr_t ;
struct TYPE_6__ {int /*<<< orphan*/  minstate; } ;
struct TYPE_10__ {TYPE_1__ valid; } ;
struct TYPE_9__ {int /*<<< orphan*/  pmsa_xpsr; int /*<<< orphan*/  pmsa_ipsr; } ;

/* Variables and functions */
 int fatal_mca (char*,...) ; 
 scalar_t__ get_target_identifier (int /*<<< orphan*/ *) ; 
 scalar_t__ mca_handler_bhhook ; 
 scalar_t__ mca_recover_range (scalar_t__) ; 
 int mca_recovered (char*) ; 
 TYPE_5__* peidx_bottom (int /*<<< orphan*/ *) ; 
 TYPE_4__* peidx_minstate_area (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
recover_from_read_error(slidx_table_t *slidx,
			peidx_table_t *peidx, pal_bus_check_info_t *pbci,
			struct ia64_sal_os_state *sos)
{
	u64 target_identifier;
	pal_min_state_area_t *pmsa;
	struct ia64_psr *psr1, *psr2;
	ia64_fptr_t *mca_hdlr_bh = (ia64_fptr_t*)mca_handler_bhhook;

	/* Is target address valid? */
	target_identifier = get_target_identifier(peidx);
	if (!target_identifier)
		return fatal_mca("target address not valid");

	/*
	 * cpu read or memory-mapped io read
	 *
	 *    offending process  affected process  OS MCA do
	 *     kernel mode        kernel mode       down system
	 *     kernel mode        user   mode       kill the process
	 *     user   mode        kernel mode       down system (*)
	 *     user   mode        user   mode       kill the process
	 *
	 * (*) You could terminate offending user-mode process
	 *    if (pbci->pv && pbci->pl != 0) *and* if you sure
	 *    the process not have any locks of kernel.
	 */

	/* Is minstate valid? */
	if (!peidx_bottom(peidx) || !(peidx_bottom(peidx)->valid.minstate))
		return fatal_mca("minstate not valid");
	psr1 =(struct ia64_psr *)&(peidx_minstate_area(peidx)->pmsa_ipsr);
	psr2 =(struct ia64_psr *)&(peidx_minstate_area(peidx)->pmsa_xpsr);

	/*
	 *  Check the privilege level of interrupted context.
	 *   If it is user-mode, then terminate affected process.
	 */

	pmsa = sos->pal_min_state;
	if (psr1->cpl != 0 ||
	   ((psr2->cpl != 0) && mca_recover_range(pmsa->pmsa_iip))) {
		/*
		 *  setup for resume to bottom half of MCA,
		 * "mca_handler_bhhook"
		 */
		/* pass to bhhook as argument (gr8, ...) */
		pmsa->pmsa_gr[8-1] = target_identifier;
		pmsa->pmsa_gr[9-1] = pmsa->pmsa_iip;
		pmsa->pmsa_gr[10-1] = pmsa->pmsa_ipsr;
		/* set interrupted return address (but no use) */
		pmsa->pmsa_br0 = pmsa->pmsa_iip;
		/* change resume address to bottom half */
		pmsa->pmsa_iip = mca_hdlr_bh->fp;
		pmsa->pmsa_gr[1-1] = mca_hdlr_bh->gp;
		/* set cpl with kernel mode */
		psr2 = (struct ia64_psr *)&pmsa->pmsa_ipsr;
		psr2->cpl = 0;
		psr2->ri  = 0;
		psr2->bn  = 1;
		psr2->i  = 0;

		return mca_recovered("user memory corruption. "
				"kill affected process - recovered.");
	}

	return fatal_mca("kernel context not recovered, iip 0x%lx\n",
			 pmsa->pmsa_iip);
}