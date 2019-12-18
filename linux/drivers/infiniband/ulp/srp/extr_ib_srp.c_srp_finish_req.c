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
struct srp_request {int dummy; } ;
struct srp_rdma_ch {int dummy; } ;
struct scsi_device {int dummy; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;

/* Variables and functions */
 struct scsi_cmnd* srp_claim_req (struct srp_rdma_ch*,struct srp_request*,struct scsi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_free_req (struct srp_rdma_ch*,struct srp_request*,struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void srp_finish_req(struct srp_rdma_ch *ch, struct srp_request *req,
			   struct scsi_device *sdev, int result)
{
	struct scsi_cmnd *scmnd = srp_claim_req(ch, req, sdev, NULL);

	if (scmnd) {
		srp_free_req(ch, req, scmnd, 0);
		scmnd->result = result;
		scmnd->scsi_done(scmnd);
	}
}