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
struct sdebug_dev_info {int /*<<< orphan*/  stopped; } ;
struct scsi_cmnd {unsigned char* cmnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEB_IN_CDB ; 
 int SDEG_RES_IMMED_MASK ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_xchg (int /*<<< orphan*/ *,int) ; 
 int check_condition_result ; 
 int /*<<< orphan*/  mk_sense_invalid_fld (struct scsi_cmnd*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int resp_start_stop(struct scsi_cmnd *scp,
			   struct sdebug_dev_info *devip)
{
	unsigned char *cmd = scp->cmnd;
	int power_cond, stop;
	bool changing;

	power_cond = (cmd[4] & 0xf0) >> 4;
	if (power_cond) {
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 4, 7);
		return check_condition_result;
	}
	stop = !(cmd[4] & 1);
	changing = atomic_read(&devip->stopped) == !stop;
	atomic_xchg(&devip->stopped, stop);
	if (!changing || cmd[1] & 0x1)  /* state unchanged or IMMED set */
		return SDEG_RES_IMMED_MASK;
	else
		return 0;
}