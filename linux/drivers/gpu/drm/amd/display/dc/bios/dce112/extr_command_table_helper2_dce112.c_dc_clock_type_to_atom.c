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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum bp_dce_clock_type { ____Placeholder_bp_dce_clock_type } bp_dce_clock_type ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
#define  DCECLOCK_TYPE_DISPLAY_CLOCK 129 
#define  DCECLOCK_TYPE_DPREFCLK 128 
 int /*<<< orphan*/  DCE_CLOCK_TYPE_DISPCLK ; 
 int /*<<< orphan*/  DCE_CLOCK_TYPE_DPREFCLK ; 

__attribute__((used)) static bool dc_clock_type_to_atom(
		enum bp_dce_clock_type id,
		uint32_t *atom_clock_type)
{
	bool retCode = true;

	if (atom_clock_type != NULL) {
		switch (id) {
		case DCECLOCK_TYPE_DISPLAY_CLOCK:
			*atom_clock_type = DCE_CLOCK_TYPE_DISPCLK;
			break;

		case DCECLOCK_TYPE_DPREFCLK:
			*atom_clock_type = DCE_CLOCK_TYPE_DPREFCLK;
			break;

		default:
			ASSERT_CRITICAL(false); /* Unhandle action in driver! */
			break;
		}
	}

	return retCode;
}