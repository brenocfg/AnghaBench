#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  unsigned long uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  init_done; } ;
struct TYPE_7__ {TYPE_1__ flags; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ FSTATE_FX00_INITIALIZED ; 
 unsigned long HZ ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int qlafx00_get_firmware_state (TYPE_2__*,scalar_t__*) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

int
qlafx00_fw_ready(scsi_qla_host_t *vha)
{
	int		rval;
	unsigned long	wtime;
	uint16_t	wait_time;	/* Wait time if loop is coming ready */
	uint32_t	state[5];

	rval = QLA_SUCCESS;

	wait_time = 10;

	/* wait time before firmware ready */
	wtime = jiffies + (wait_time * HZ);

	/* Wait for ISP to finish init */
	if (!vha->flags.init_done)
		ql_dbg(ql_dbg_init, vha, 0x013a,
		    "Waiting for init to complete...\n");

	do {
		rval = qlafx00_get_firmware_state(vha, state);

		if (rval == QLA_SUCCESS) {
			if (state[0] == FSTATE_FX00_INITIALIZED) {
				ql_dbg(ql_dbg_init, vha, 0x013b,
				    "fw_state=%x\n", state[0]);
				rval = QLA_SUCCESS;
					break;
			}
		}
		rval = QLA_FUNCTION_FAILED;

		if (time_after_eq(jiffies, wtime))
			break;

		/* Delay for a while */
		msleep(500);

		ql_dbg(ql_dbg_init, vha, 0x013c,
		    "fw_state=%x curr time=%lx.\n", state[0], jiffies);
	} while (1);


	if (rval)
		ql_dbg(ql_dbg_init, vha, 0x013d,
		    "Firmware ready **** FAILED ****.\n");
	else
		ql_dbg(ql_dbg_init, vha, 0x013e,
		    "Firmware ready **** SUCCESS ****.\n");

	return rval;
}