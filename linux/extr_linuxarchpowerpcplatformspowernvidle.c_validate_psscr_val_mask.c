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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int ERR_DEEP_STATE_ESL_MISMATCH ; 
 int ERR_EC_ESL_MISMATCH ; 
 scalar_t__ GET_PSSCR_EC (int) ; 
 scalar_t__ GET_PSSCR_ESL (int) ; 
 int OPAL_PM_LOSE_FULL_CONTEXT ; 
 int PSSCR_HV_DEFAULT_MASK ; 
 int PSSCR_HV_DEFAULT_VAL ; 

int validate_psscr_val_mask(u64 *psscr_val, u64 *psscr_mask, u32 flags)
{
	int err = 0;

	/*
	 * psscr_mask == 0xf indicates an older firmware.
	 * Set remaining fields of psscr to the default values.
	 * See NOTE above definition of PSSCR_HV_DEFAULT_VAL
	 */
	if (*psscr_mask == 0xf) {
		*psscr_val = *psscr_val | PSSCR_HV_DEFAULT_VAL;
		*psscr_mask = PSSCR_HV_DEFAULT_MASK;
		return err;
	}

	/*
	 * New firmware is expected to set the psscr_val bits correctly.
	 * Validate that the following invariants are correctly maintained by
	 * the new firmware.
	 * - ESL bit value matches the EC bit value.
	 * - ESL bit is set for all the deep stop states.
	 */
	if (GET_PSSCR_ESL(*psscr_val) != GET_PSSCR_EC(*psscr_val)) {
		err = ERR_EC_ESL_MISMATCH;
	} else if ((flags & OPAL_PM_LOSE_FULL_CONTEXT) &&
		GET_PSSCR_ESL(*psscr_val) == 0) {
		err = ERR_DEEP_STATE_ESL_MISMATCH;
	}

	return err;
}