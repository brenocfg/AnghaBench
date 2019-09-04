#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct pt_regs {int dsisr; int dar; } ;
struct TYPE_3__ {int /*<<< orphan*/  link_error_type; int /*<<< orphan*/  ra_error_type; int /*<<< orphan*/  user_error_type; int /*<<< orphan*/  tlb_error_type; int /*<<< orphan*/  erat_error_type; int /*<<< orphan*/  slb_error_type; int /*<<< orphan*/  ue_error_type; } ;
struct mce_error_info {int error_type; int /*<<< orphan*/  initiator; int /*<<< orphan*/  severity; TYPE_1__ u; } ;
struct mce_derror_table {int dsisr_value; int error_type; scalar_t__ dar_valid; int /*<<< orphan*/  initiator; int /*<<< orphan*/  severity; int /*<<< orphan*/  error_subtype; } ;
struct TYPE_4__ {scalar_t__ in_mce; } ;

/* Variables and functions */
 scalar_t__ MAX_MCE_DEPTH ; 
#define  MCE_ERROR_TYPE_ERAT 134 
#define  MCE_ERROR_TYPE_LINK 133 
#define  MCE_ERROR_TYPE_RA 132 
#define  MCE_ERROR_TYPE_SLB 131 
#define  MCE_ERROR_TYPE_TLB 130 
#define  MCE_ERROR_TYPE_UE 129 
 int MCE_ERROR_TYPE_UNKNOWN ; 
#define  MCE_ERROR_TYPE_USER 128 
 int /*<<< orphan*/  MCE_FLUSH_ERAT ; 
 int /*<<< orphan*/  MCE_FLUSH_SLB ; 
 int /*<<< orphan*/  MCE_FLUSH_TLB ; 
 int /*<<< orphan*/  MCE_INITIATOR_CPU ; 
 int /*<<< orphan*/  MCE_SEV_ERROR_SYNC ; 
 TYPE_2__* get_paca () ; 
 int /*<<< orphan*/  mce_find_instr_ea_and_pfn (struct pt_regs*,int*,int*) ; 
 int /*<<< orphan*/  mce_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mce_handle_derror(struct pt_regs *regs,
		const struct mce_derror_table table[],
		struct mce_error_info *mce_err, uint64_t *addr,
		uint64_t *phys_addr)
{
	uint64_t dsisr = regs->dsisr;
	int handled = 0;
	int found = 0;
	int i;

	*addr = 0;

	for (i = 0; table[i].dsisr_value; i++) {
		if (!(dsisr & table[i].dsisr_value))
			continue;

		/* attempt to correct the error */
		switch (table[i].error_type) {
		case MCE_ERROR_TYPE_SLB:
			if (mce_flush(MCE_FLUSH_SLB))
				handled = 1;
			break;
		case MCE_ERROR_TYPE_ERAT:
			if (mce_flush(MCE_FLUSH_ERAT))
				handled = 1;
			break;
		case MCE_ERROR_TYPE_TLB:
			if (mce_flush(MCE_FLUSH_TLB))
				handled = 1;
			break;
		}

		/*
		 * Attempt to handle multiple conditions, but only return
		 * one. Ensure uncorrectable errors are first in the table
		 * to match.
		 */
		if (found)
			continue;

		/* now fill in mce_error_info */
		mce_err->error_type = table[i].error_type;
		switch (table[i].error_type) {
		case MCE_ERROR_TYPE_UE:
			mce_err->u.ue_error_type = table[i].error_subtype;
			break;
		case MCE_ERROR_TYPE_SLB:
			mce_err->u.slb_error_type = table[i].error_subtype;
			break;
		case MCE_ERROR_TYPE_ERAT:
			mce_err->u.erat_error_type = table[i].error_subtype;
			break;
		case MCE_ERROR_TYPE_TLB:
			mce_err->u.tlb_error_type = table[i].error_subtype;
			break;
		case MCE_ERROR_TYPE_USER:
			mce_err->u.user_error_type = table[i].error_subtype;
			break;
		case MCE_ERROR_TYPE_RA:
			mce_err->u.ra_error_type = table[i].error_subtype;
			break;
		case MCE_ERROR_TYPE_LINK:
			mce_err->u.link_error_type = table[i].error_subtype;
			break;
		}
		mce_err->severity = table[i].severity;
		mce_err->initiator = table[i].initiator;
		if (table[i].dar_valid)
			*addr = regs->dar;
		else if (mce_err->severity == MCE_SEV_ERROR_SYNC &&
				table[i].error_type == MCE_ERROR_TYPE_UE) {
			/*
			 * We do a maximum of 4 nested MCE calls, see
			 * kernel/exception-64s.h
			 */
			if (get_paca()->in_mce < MAX_MCE_DEPTH)
				mce_find_instr_ea_and_pfn(regs, addr, phys_addr);
		}
		found = 1;
	}

	if (found)
		return handled;

	mce_err->error_type = MCE_ERROR_TYPE_UNKNOWN;
	mce_err->severity = MCE_SEV_ERROR_SYNC;
	mce_err->initiator = MCE_INITIATOR_CPU;

	return 0;
}