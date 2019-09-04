#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ select_delay; } ;
struct TYPE_7__ {scalar_t__ select_date; int /*<<< orphan*/  spinup_date; scalar_t__ first_read_date; } ;
struct TYPE_6__ {int dor; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 TYPE_4__* DP ; 
 TYPE_3__* DRS ; 
 TYPE_2__* FDCS ; 
 int FD_RAW_NO_MOTOR ; 
 int UNIT (scalar_t__) ; 
 scalar_t__ current_drive ; 
 int /*<<< orphan*/  del_timer (scalar_t__) ; 
 int fd_wait_for_completion (scalar_t__,void (*) ()) ; 
 int /*<<< orphan*/  fdc ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ motor_off_timer ; 
 TYPE_1__* raw_cmd ; 
 int /*<<< orphan*/  set_debugt () ; 
 int /*<<< orphan*/  set_dor (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int start_motor(void (*function)(void))
{
	int mask;
	int data;

	mask = 0xfc;
	data = UNIT(current_drive);
	if (!(raw_cmd->flags & FD_RAW_NO_MOTOR)) {
		if (!(FDCS->dor & (0x10 << UNIT(current_drive)))) {
			set_debugt();
			/* no read since this drive is running */
			DRS->first_read_date = 0;
			/* note motor start time if motor is not yet running */
			DRS->spinup_date = jiffies;
			data |= (0x10 << UNIT(current_drive));
		}
	} else if (FDCS->dor & (0x10 << UNIT(current_drive)))
		mask &= ~(0x10 << UNIT(current_drive));

	/* starts motor and selects floppy */
	del_timer(motor_off_timer + current_drive);
	set_dor(fdc, mask, data);

	/* wait_for_completion also schedules reset if needed. */
	return fd_wait_for_completion(DRS->select_date + DP->select_delay,
				      function);
}