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
struct cyapa {scalar_t__ state; int operational; int* status; } ;

/* Variables and functions */
 int BL_STATUS_WATCHDOG ; 
 int /*<<< orphan*/  CYAPA_CMD_SOFT_RESET ; 
 scalar_t__ CYAPA_STATE_BL_IDLE ; 
 scalar_t__ CYAPA_STATE_NO_DEVICE ; 
 scalar_t__ CYAPA_STATE_OP ; 
 int EAGAIN ; 
 int EIO ; 
 int ETIMEDOUT ; 
 size_t REG_BL_STATUS ; 
 int cyapa_poll_state (struct cyapa*,int) ; 
 int cyapa_write_byte (struct cyapa*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cyapa_gen3_bl_enter(struct cyapa *cyapa)
{
	int error;
	int waiting_time;

	error = cyapa_poll_state(cyapa, 500);
	if (error)
		return error;
	if (cyapa->state == CYAPA_STATE_BL_IDLE) {
		/* Already in BL_IDLE. Skipping reset. */
		return 0;
	}

	if (cyapa->state != CYAPA_STATE_OP)
		return -EAGAIN;

	cyapa->operational = false;
	cyapa->state = CYAPA_STATE_NO_DEVICE;
	error = cyapa_write_byte(cyapa, CYAPA_CMD_SOFT_RESET, 0x01);
	if (error)
		return -EIO;

	usleep_range(25000, 50000);
	waiting_time = 2000;  /* For some shipset, max waiting time is 1~2s. */
	do {
		error = cyapa_poll_state(cyapa, 500);
		if (error) {
			if (error == -ETIMEDOUT) {
				waiting_time -= 500;
				continue;
			}
			return error;
		}

		if ((cyapa->state == CYAPA_STATE_BL_IDLE) &&
			!(cyapa->status[REG_BL_STATUS] & BL_STATUS_WATCHDOG))
			break;

		msleep(100);
		waiting_time -= 100;
	} while (waiting_time > 0);

	if ((cyapa->state != CYAPA_STATE_BL_IDLE) ||
		(cyapa->status[REG_BL_STATUS] & BL_STATUS_WATCHDOG))
		return -EAGAIN;

	return 0;
}