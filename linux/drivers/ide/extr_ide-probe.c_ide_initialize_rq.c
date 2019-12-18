#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sense; } ;
struct ide_request {int /*<<< orphan*/  sense; TYPE_1__ sreq; int /*<<< orphan*/ * special; } ;

/* Variables and functions */
 struct ide_request* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  scsi_req_init (TYPE_1__*) ; 

__attribute__((used)) static void ide_initialize_rq(struct request *rq)
{
	struct ide_request *req = blk_mq_rq_to_pdu(rq);

	req->special = NULL;
	scsi_req_init(&req->sreq);
	req->sreq.sense = req->sense;
}