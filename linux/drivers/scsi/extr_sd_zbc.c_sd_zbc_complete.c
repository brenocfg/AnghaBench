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
struct scsi_sense_hdr {scalar_t__ sense_key; int asc; } ;
struct scsi_cmnd {int result; struct request* request; } ;
struct request {int /*<<< orphan*/  rq_flags; } ;

/* Variables and functions */
 scalar_t__ ILLEGAL_REQUEST ; 
 scalar_t__ REQ_OP_ZONE_RESET ; 
 int /*<<< orphan*/  RQF_QUIET ; 
 scalar_t__ req_op (struct request*) ; 

void sd_zbc_complete(struct scsi_cmnd *cmd, unsigned int good_bytes,
		     struct scsi_sense_hdr *sshdr)
{
	int result = cmd->result;
	struct request *rq = cmd->request;

	if (req_op(rq) == REQ_OP_ZONE_RESET &&
	    result &&
	    sshdr->sense_key == ILLEGAL_REQUEST &&
	    sshdr->asc == 0x24) {
		/*
		 * INVALID FIELD IN CDB error: reset of a conventional
		 * zone was attempted. Nothing to worry about, so be
		 * quiet about the error.
		 */
		rq->rq_flags |= RQF_QUIET;
	}
}