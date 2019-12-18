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
typedef  scalar_t__ u64 ;
struct scm_request {int retries; void* next_aidaw; int /*<<< orphan*/  error; struct scm_blk_dev* bdev; struct aob* request; struct aob* aob; } ;
struct scm_blk_dev {int /*<<< orphan*/  scmdev; } ;
struct aob_rq_header {int /*<<< orphan*/  scmdev; } ;
struct TYPE_2__ {scalar_t__ data; int /*<<< orphan*/  cmd_code; } ;
struct aob {int /*<<< orphan*/ * msb; TYPE_1__ request; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARQB_CMD_MOVE ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  memset (struct aob*,int /*<<< orphan*/ ,int) ; 
 int nr_requests_per_io ; 
 struct aob_rq_header* to_aobrq (struct scm_request*) ; 

__attribute__((used)) static inline void scm_request_init(struct scm_blk_dev *bdev,
				    struct scm_request *scmrq)
{
	struct aob_rq_header *aobrq = to_aobrq(scmrq);
	struct aob *aob = scmrq->aob;

	memset(scmrq->request, 0,
	       nr_requests_per_io * sizeof(scmrq->request[0]));
	memset(aob, 0, sizeof(*aob));
	aobrq->scmdev = bdev->scmdev;
	aob->request.cmd_code = ARQB_CMD_MOVE;
	aob->request.data = (u64) aobrq;
	scmrq->bdev = bdev;
	scmrq->retries = 4;
	scmrq->error = BLK_STS_OK;
	/* We don't use all msbs - place aidaws at the end of the aob page. */
	scmrq->next_aidaw = (void *) &aob->msb[nr_requests_per_io];
}