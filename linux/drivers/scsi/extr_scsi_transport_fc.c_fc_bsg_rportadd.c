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
struct request_queue {int dummy; } ;
struct device {int dummy; } ;
struct fc_rport {struct request_queue* rqst_q; struct device dev; } ;
struct fc_internal {TYPE_1__* f; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
struct TYPE_2__ {int /*<<< orphan*/  dd_bsg_size; int /*<<< orphan*/  bsg_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_DEFAULT_SG_TIMEOUT ; 
 int ENOTSUPP ; 
 scalar_t__ IS_ERR (struct request_queue*) ; 
 int PTR_ERR (struct request_queue*) ; 
 int /*<<< orphan*/  __scsi_init_queue (struct Scsi_Host*,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_rq_timeout (struct request_queue*,int /*<<< orphan*/ ) ; 
 struct request_queue* bsg_setup_queue (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  fc_bsg_dispatch_prep ; 
 int /*<<< orphan*/  fc_bsg_job_timeout ; 
 struct fc_internal* to_fc_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fc_bsg_rportadd(struct Scsi_Host *shost, struct fc_rport *rport)
{
	struct device *dev = &rport->dev;
	struct fc_internal *i = to_fc_internal(shost->transportt);
	struct request_queue *q;

	rport->rqst_q = NULL;

	if (!i->f->bsg_request)
		return -ENOTSUPP;

	q = bsg_setup_queue(dev, dev_name(dev), fc_bsg_dispatch_prep,
				fc_bsg_job_timeout, i->f->dd_bsg_size);
	if (IS_ERR(q)) {
		dev_err(dev, "failed to setup bsg queue\n");
		return PTR_ERR(q);
	}
	__scsi_init_queue(shost, q);
	blk_queue_rq_timeout(q, BLK_DEFAULT_SG_TIMEOUT);
	rport->rqst_q = q;
	return 0;
}