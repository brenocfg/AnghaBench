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
struct scsi_cmnd {int tag; unsigned char* host_scribble; TYPE_1__* request; } ;
struct request_queue {int dummy; } ;
struct request {int tag; } ;
struct fnic {int dummy; } ;
struct TYPE_2__ {int tag; struct request_queue* q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_REQ_NOWAIT ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int SCSI_NO_TAG ; 
 struct request* blk_mq_alloc_request (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
fnic_scsi_host_start_tag(struct fnic *fnic, struct scsi_cmnd *sc)
{
	struct request_queue *q = sc->request->q;
	struct request *dummy;

	dummy = blk_mq_alloc_request(q, REQ_OP_WRITE, BLK_MQ_REQ_NOWAIT);
	if (IS_ERR(dummy))
		return SCSI_NO_TAG;

	sc->tag = sc->request->tag = dummy->tag;
	sc->host_scribble = (unsigned char *)dummy;

	return dummy->tag;
}