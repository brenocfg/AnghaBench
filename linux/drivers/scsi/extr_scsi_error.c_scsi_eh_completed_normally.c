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
struct scsi_cmnd {int /*<<< orphan*/  device; int /*<<< orphan*/ * cmnd; int /*<<< orphan*/  result; } ;

/* Variables and functions */
#define  BUSY 136 
#define  CHECK_CONDITION 135 
 scalar_t__ COMMAND_COMPLETE ; 
#define  COMMAND_TERMINATED 134 
#define  CONDITION_GOOD 133 
 scalar_t__ DID_OK ; 
 scalar_t__ DID_RESET ; 
 int FAILED ; 
#define  GOOD 132 
#define  INTERMEDIATE_C_GOOD 131 
#define  INTERMEDIATE_GOOD 130 
 int NEEDS_RETRY ; 
#define  QUEUE_FULL 129 
#define  RESERVATION_CONFLICT 128 
 int SUCCESS ; 
 int /*<<< orphan*/  TEST_UNIT_READY ; 
 scalar_t__ host_byte (int /*<<< orphan*/ ) ; 
 scalar_t__ msg_byte (int /*<<< orphan*/ ) ; 
 int scsi_check_sense (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_handle_queue_full (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_handle_queue_ramp_up (int /*<<< orphan*/ ) ; 
 int status_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scsi_eh_completed_normally(struct scsi_cmnd *scmd)
{
	/*
	 * first check the host byte, to see if there is anything in there
	 * that would indicate what we need to do.
	 */
	if (host_byte(scmd->result) == DID_RESET) {
		/*
		 * rats.  we are already in the error handler, so we now
		 * get to try and figure out what to do next.  if the sense
		 * is valid, we have a pretty good idea of what to do.
		 * if not, we mark it as FAILED.
		 */
		return scsi_check_sense(scmd);
	}
	if (host_byte(scmd->result) != DID_OK)
		return FAILED;

	/*
	 * next, check the message byte.
	 */
	if (msg_byte(scmd->result) != COMMAND_COMPLETE)
		return FAILED;

	/*
	 * now, check the status byte to see if this indicates
	 * anything special.
	 */
	switch (status_byte(scmd->result)) {
	case GOOD:
		scsi_handle_queue_ramp_up(scmd->device);
		/* FALLTHROUGH */
	case COMMAND_TERMINATED:
		return SUCCESS;
	case CHECK_CONDITION:
		return scsi_check_sense(scmd);
	case CONDITION_GOOD:
	case INTERMEDIATE_GOOD:
	case INTERMEDIATE_C_GOOD:
		/*
		 * who knows?  FIXME(eric)
		 */
		return SUCCESS;
	case RESERVATION_CONFLICT:
		if (scmd->cmnd[0] == TEST_UNIT_READY)
			/* it is a success, we probed the device and
			 * found it */
			return SUCCESS;
		/* otherwise, we failed to send the command */
		return FAILED;
	case QUEUE_FULL:
		scsi_handle_queue_full(scmd->device);
		/* fall through */
	case BUSY:
		return NEEDS_RETRY;
	default:
		return FAILED;
	}
	return FAILED;
}