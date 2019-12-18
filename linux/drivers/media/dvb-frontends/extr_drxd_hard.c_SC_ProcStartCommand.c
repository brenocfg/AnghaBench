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
struct drxd_state {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int Read16 (struct drxd_state*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_COMM_EXEC__A ; 
 int /*<<< orphan*/  SC_RA_RAM_CMD_ADDR__A ; 
 int /*<<< orphan*/  SC_RA_RAM_CMD_PROC_START ; 
 int /*<<< orphan*/  SC_RA_RAM_PARAM0__A ; 
 int /*<<< orphan*/  SC_RA_RAM_PARAM1__A ; 
 int /*<<< orphan*/  SC_SendCommand (struct drxd_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_WaitForReady (struct drxd_state*) ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int SC_ProcStartCommand(struct drxd_state *state,
			       u16 subCmd, u16 param0, u16 param1)
{
	int ret, status = 0;
	u16 scExec;

	mutex_lock(&state->mutex);
	do {
		ret = Read16(state, SC_COMM_EXEC__A, &scExec, 0);
		if (ret < 0 || scExec != 1) {
			status = -1;
			break;
		}
		SC_WaitForReady(state);
		status |= Write16(state, SC_RA_RAM_CMD_ADDR__A, subCmd, 0);
		status |= Write16(state, SC_RA_RAM_PARAM1__A, param1, 0);
		status |= Write16(state, SC_RA_RAM_PARAM0__A, param0, 0);

		SC_SendCommand(state, SC_RA_RAM_CMD_PROC_START);
	} while (0);
	mutex_unlock(&state->mutex);
	return status;
}