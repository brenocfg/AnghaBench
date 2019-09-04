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
struct drxd_state {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int HI_Command (struct drxd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HI_RA_RAM_SRV_CMD_RESET ; 
 int /*<<< orphan*/  HI_RA_RAM_SRV_RST_KEY_ACT ; 
 int /*<<< orphan*/  HI_RA_RAM_SRV_RST_KEY__A ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int HI_ResetCommand(struct drxd_state *state)
{
	int status;

	mutex_lock(&state->mutex);
	status = Write16(state, HI_RA_RAM_SRV_RST_KEY__A,
			 HI_RA_RAM_SRV_RST_KEY_ACT, 0);
	if (status == 0)
		status = HI_Command(state, HI_RA_RAM_SRV_CMD_RESET, NULL);
	mutex_unlock(&state->mutex);
	msleep(1);
	return status;
}