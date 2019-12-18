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
typedef  int u8 ;
struct scsi_cmnd {int* cmnd; int result; } ;

/* Variables and functions */
 int ILLEGAL_REQUEST ; 
#define  SET_WINDOW 129 
#define  WRITE_SAME 128 

__attribute__((used)) static bool storvsc_scsi_cmd_ok(struct scsi_cmnd *scmnd)
{
	bool allowed = true;
	u8 scsi_op = scmnd->cmnd[0];

	switch (scsi_op) {
	/* the host does not handle WRITE_SAME, log accident usage */
	case WRITE_SAME:
	/*
	 * smartd sends this command and the host does not handle
	 * this. So, don't send it.
	 */
	case SET_WINDOW:
		scmnd->result = ILLEGAL_REQUEST << 16;
		allowed = false;
		break;
	default:
		break;
	}
	return allowed;
}