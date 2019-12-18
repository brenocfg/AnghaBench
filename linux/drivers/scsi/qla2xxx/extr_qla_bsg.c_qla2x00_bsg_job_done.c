#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fc_bsg_reply {int result; int /*<<< orphan*/  reply_payload_rcv_len; } ;
struct bsg_job {struct fc_bsg_reply* reply; } ;
struct TYPE_5__ {struct bsg_job* bsg_job; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* free ) (TYPE_2__*) ;TYPE_1__ u; } ;
typedef  TYPE_2__ srb_t ;

/* Variables and functions */
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void qla2x00_bsg_job_done(srb_t *sp, int res)
{
	struct bsg_job *bsg_job = sp->u.bsg_job;
	struct fc_bsg_reply *bsg_reply = bsg_job->reply;

	bsg_reply->result = res;
	bsg_job_done(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	sp->free(sp);
}