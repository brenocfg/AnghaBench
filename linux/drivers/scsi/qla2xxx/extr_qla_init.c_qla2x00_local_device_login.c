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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
typedef  int /*<<< orphan*/  mb ;
typedef  int /*<<< orphan*/  fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_0 ; 
 int MAILBOX_REGISTER_COUNT ; 
 scalar_t__ MBS_COMMAND_ERROR ; 
 scalar_t__ MBS_COMMAND_PARAMETER_ERROR ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int qla2x00_login_local_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 

int
qla2x00_local_device_login(scsi_qla_host_t *vha, fc_port_t *fcport)
{
	int		rval;
	uint16_t	mb[MAILBOX_REGISTER_COUNT];

	memset(mb, 0, sizeof(mb));
	rval = qla2x00_login_local_device(vha, fcport, mb, BIT_0);
	if (rval == QLA_SUCCESS) {
		/* Interrogate mailbox registers for any errors */
		if (mb[0] == MBS_COMMAND_ERROR)
			rval = 1;
		else if (mb[0] == MBS_COMMAND_PARAMETER_ERROR)
			/* device not in PCB table */
			rval = 3;
	}

	return (rval);
}