#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_request {scalar_t__ waiting; int /*<<< orphan*/  sense; struct bio* bio; int /*<<< orphan*/  result; struct scsi_tape* stp; } ;
struct scsi_tape {TYPE_2__* buffer; } ;
struct scsi_request {int /*<<< orphan*/  sense; scalar_t__ sense_len; int /*<<< orphan*/  resid_len; int /*<<< orphan*/  result; } ;
struct request {struct st_request* end_io_data; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  residual; int /*<<< orphan*/  midlevel_result; } ;
struct TYPE_4__ {TYPE_1__ cmdstat; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int /*<<< orphan*/  blk_rq_unmap_user (struct bio*) ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct scsi_request* scsi_req (struct request*) ; 
 int /*<<< orphan*/  st_do_stats (struct scsi_tape*,struct request*) ; 

__attribute__((used)) static void st_scsi_execute_end(struct request *req, blk_status_t status)
{
	struct st_request *SRpnt = req->end_io_data;
	struct scsi_request *rq = scsi_req(req);
	struct scsi_tape *STp = SRpnt->stp;
	struct bio *tmp;

	STp->buffer->cmdstat.midlevel_result = SRpnt->result = rq->result;
	STp->buffer->cmdstat.residual = rq->resid_len;

	st_do_stats(STp, req);

	tmp = SRpnt->bio;
	if (rq->sense_len)
		memcpy(SRpnt->sense, rq->sense, SCSI_SENSE_BUFFERSIZE);
	if (SRpnt->waiting)
		complete(SRpnt->waiting);

	blk_rq_unmap_user(tmp);
	blk_put_request(req);
}