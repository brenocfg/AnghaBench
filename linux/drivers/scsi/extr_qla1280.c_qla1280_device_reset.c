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
typedef  int uint16_t ;
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_1 ; 
 int BIT_2 ; 
 int BIT_7 ; 
 int /*<<< orphan*/  ENTER (char*) ; 
 int /*<<< orphan*/  LEAVE (char*) ; 
 int MAILBOX_REGISTER_COUNT ; 
 int MBC_ABORT_TARGET ; 
 int /*<<< orphan*/  MK_SYNC_ID ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int qla1280_mailbox_command (struct scsi_qla_host*,int,int*) ; 
 int /*<<< orphan*/  qla1280_marker (struct scsi_qla_host*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla1280_device_reset(struct scsi_qla_host *ha, int bus, int target)
{
	uint16_t mb[MAILBOX_REGISTER_COUNT];
	int status;

	ENTER("qla1280_device_reset");

	mb[0] = MBC_ABORT_TARGET;
	mb[1] = (bus ? (target | BIT_7) : target) << 8;
	mb[2] = 1;
	status = qla1280_mailbox_command(ha, BIT_2 | BIT_1 | BIT_0, &mb[0]);

	/* Issue marker command. */
	qla1280_marker(ha, bus, target, 0, MK_SYNC_ID);

	if (status)
		dprintk(2, "qla1280_device_reset: **** FAILED ****\n");

	LEAVE("qla1280_device_reset");
	return status;
}