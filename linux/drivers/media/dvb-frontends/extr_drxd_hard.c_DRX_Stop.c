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
typedef  int /*<<< orphan*/  u32 ;
struct drxd_state {scalar_t__ drxd_state; scalar_t__ cscd_state; scalar_t__ type_A; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_CE_COMM_EXEC__A ; 
 int /*<<< orphan*/  B_CP_COMM_EXEC__A ; 
 int /*<<< orphan*/  B_EQ_COMM_EXEC__A ; 
 int /*<<< orphan*/  B_FT_COMM_EXEC__A ; 
 int /*<<< orphan*/  B_LC_COMM_EXEC__A ; 
 int /*<<< orphan*/  B_SC_COMM_EXEC__A ; 
 scalar_t__ CSCD_SAVED ; 
 int ConfigureMPEGOutput (struct drxd_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ DRXD_STARTED ; 
 scalar_t__ DRXD_STOPPED ; 
 int DRX_GetLockStatus (struct drxd_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_OD_REG_COMM_EXEC__A ; 
 int /*<<< orphan*/  LC_COMM_EXEC__A ; 
 int SC_COMM_EXEC_CTL_STOP ; 
 int /*<<< orphan*/  SC_COMM_EXEC__A ; 
 int StopOC (struct drxd_state*) ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int DRX_Stop(struct drxd_state *state)
{
	int status;

	if (state->drxd_state != DRXD_STARTED)
		return 0;

	do {
		if (state->cscd_state != CSCD_SAVED) {
			u32 lock;
			status = DRX_GetLockStatus(state, &lock);
			if (status < 0)
				break;
		}

		status = StopOC(state);
		if (status < 0)
			break;

		state->drxd_state = DRXD_STOPPED;

		status = ConfigureMPEGOutput(state, 0);
		if (status < 0)
			break;

		if (state->type_A) {
			/* Stop relevant processors off the device */
			status = Write16(state, EC_OD_REG_COMM_EXEC__A, 0x0000, 0x0000);
			if (status < 0)
				break;

			status = Write16(state, SC_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			if (status < 0)
				break;
			status = Write16(state, LC_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			if (status < 0)
				break;
		} else {
			/* Stop all processors except HI & CC & FE */
			status = Write16(state, B_SC_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			if (status < 0)
				break;
			status = Write16(state, B_LC_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			if (status < 0)
				break;
			status = Write16(state, B_FT_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			if (status < 0)
				break;
			status = Write16(state, B_CP_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			if (status < 0)
				break;
			status = Write16(state, B_CE_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			if (status < 0)
				break;
			status = Write16(state, B_EQ_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			if (status < 0)
				break;
			status = Write16(state, EC_OD_REG_COMM_EXEC__A, 0x0000, 0);
			if (status < 0)
				break;
		}

	} while (0);
	return status;
}