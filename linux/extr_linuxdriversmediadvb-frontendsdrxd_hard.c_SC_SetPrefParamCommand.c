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
typedef  int /*<<< orphan*/  u16 ;
struct drxd_state {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  SC_RA_RAM_CMD_ADDR__A ; 
 int /*<<< orphan*/  SC_RA_RAM_CMD_SET_PREF_PARAM ; 
 int /*<<< orphan*/  SC_RA_RAM_PARAM0__A ; 
 int /*<<< orphan*/  SC_RA_RAM_PARAM1__A ; 
 int SC_SendCommand (struct drxd_state*,int /*<<< orphan*/ ) ; 
 int SC_WaitForReady (struct drxd_state*) ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int SC_SetPrefParamCommand(struct drxd_state *state,
				  u16 subCmd, u16 param0, u16 param1)
{
	int status;

	mutex_lock(&state->mutex);
	do {
		status = SC_WaitForReady(state);
		if (status < 0)
			break;
		status = Write16(state, SC_RA_RAM_CMD_ADDR__A, subCmd, 0);
		if (status < 0)
			break;
		status = Write16(state, SC_RA_RAM_PARAM1__A, param1, 0);
		if (status < 0)
			break;
		status = Write16(state, SC_RA_RAM_PARAM0__A, param0, 0);
		if (status < 0)
			break;

		status = SC_SendCommand(state, SC_RA_RAM_CMD_SET_PREF_PARAM);
		if (status < 0)
			break;
	} while (0);
	mutex_unlock(&state->mutex);
	return status;
}