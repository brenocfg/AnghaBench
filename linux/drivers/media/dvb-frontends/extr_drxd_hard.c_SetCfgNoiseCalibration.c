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
typedef  int u16 ;
struct drxd_state {int /*<<< orphan*/  type_A; } ;
struct SNoiseCal {int cpNexpOfs; int tdCal2k; int tdCal8k; scalar_t__ cpOpt; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_SC_RA_RAM_CO_TD_CAL_2K__A ; 
 int /*<<< orphan*/  B_SC_RA_RAM_CO_TD_CAL_8K__A ; 
 int /*<<< orphan*/  CP_REG_AC_NEXP_OFFS__A ; 
 int Read16 (struct drxd_state*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int SC_RA_RAM_BE_OPT_ENA_CP_OPT ; 
 int /*<<< orphan*/  SC_RA_RAM_BE_OPT_ENA__A ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SetCfgNoiseCalibration(struct drxd_state *state,
				  struct SNoiseCal *noiseCal)
{
	u16 beOptEna;
	int status = 0;

	do {
		status = Read16(state, SC_RA_RAM_BE_OPT_ENA__A, &beOptEna, 0);
		if (status < 0)
			break;
		if (noiseCal->cpOpt) {
			beOptEna |= (1 << SC_RA_RAM_BE_OPT_ENA_CP_OPT);
		} else {
			beOptEna &= ~(1 << SC_RA_RAM_BE_OPT_ENA_CP_OPT);
			status = Write16(state, CP_REG_AC_NEXP_OFFS__A, noiseCal->cpNexpOfs, 0);
			if (status < 0)
				break;
		}
		status = Write16(state, SC_RA_RAM_BE_OPT_ENA__A, beOptEna, 0);
		if (status < 0)
			break;

		if (!state->type_A) {
			status = Write16(state, B_SC_RA_RAM_CO_TD_CAL_2K__A, noiseCal->tdCal2k, 0);
			if (status < 0)
				break;
			status = Write16(state, B_SC_RA_RAM_CO_TD_CAL_8K__A, noiseCal->tdCal8k, 0);
			if (status < 0)
				break;
		}
	} while (0);

	return status;
}