#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ia64_sal_os_state {int rv_rc; } ;
typedef  int /*<<< orphan*/  peidx_table_t ;
struct TYPE_4__ {scalar_t__ uc; scalar_t__ rc; scalar_t__ cc; scalar_t__ tc; } ;
typedef  TYPE_1__ pal_processor_state_info_t ;
struct TYPE_5__ {int bsi; scalar_t__ eb; scalar_t__ ib; } ;
typedef  TYPE_2__ pal_bus_check_info_t ;
typedef  int /*<<< orphan*/  mca_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  MCA_IS_GLOBAL ; 
 int /*<<< orphan*/  MCA_IS_LOCAL ; 
 scalar_t__ peidx_psp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mca_type_t
is_mca_global(peidx_table_t *peidx, pal_bus_check_info_t *pbci,
	      struct ia64_sal_os_state *sos)
{
	pal_processor_state_info_t *psp =
		(pal_processor_state_info_t*)peidx_psp(peidx);

	/*
	 * PAL can request a rendezvous, if the MCA has a global scope.
	 * If "rz_always" flag is set, SAL requests MCA rendezvous
	 * in spite of global MCA.
	 * Therefore it is local MCA when rendezvous has not been requested.
	 * Failed to rendezvous, the system must be down.
	 */
	switch (sos->rv_rc) {
		case -1: /* SAL rendezvous unsuccessful */
			return MCA_IS_GLOBAL;
		case  0: /* SAL rendezvous not required */
			return MCA_IS_LOCAL;
		case  1: /* SAL rendezvous successful int */
		case  2: /* SAL rendezvous successful int with init */
		default:
			break;
	}

	/*
	 * If One or more Cache/TLB/Reg_File/Uarch_Check is here,
	 * it would be a local MCA. (i.e. processor internal error)
	 */
	if (psp->tc || psp->cc || psp->rc || psp->uc)
		return MCA_IS_LOCAL;
	
	/*
	 * Bus_Check structure with Bus_Check.ib (internal bus error) flag set
	 * would be a global MCA. (e.g. a system bus address parity error)
	 */
	if (!pbci || pbci->ib)
		return MCA_IS_GLOBAL;

	/*
	 * Bus_Check structure with Bus_Check.eb (external bus error) flag set
	 * could be either a local MCA or a global MCA.
	 *
	 * Referring Bus_Check.bsi:
	 *   0: Unknown/unclassified
	 *   1: BERR#
	 *   2: BINIT#
	 *   3: Hard Fail
	 * (FIXME: Are these SGI specific or generic bsi values?)
	 */
	if (pbci->eb)
		switch (pbci->bsi) {
			case 0:
				/* e.g. a load from poisoned memory */
				return MCA_IS_LOCAL;
			case 1:
			case 2:
			case 3:
				return MCA_IS_GLOBAL;
		}

	return MCA_IS_GLOBAL;
}