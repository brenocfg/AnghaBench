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
struct request {int rq_flags; } ;

/* Variables and functions */
 int RQF_DONTPREP ; 
 int /*<<< orphan*/  blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  scsi_mq_uninit_cmd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsi_cleanup_rq(struct request *rq)
{
	if (rq->rq_flags & RQF_DONTPREP) {
		scsi_mq_uninit_cmd(blk_mq_rq_to_pdu(rq));
		rq->rq_flags &= ~RQF_DONTPREP;
	}
}