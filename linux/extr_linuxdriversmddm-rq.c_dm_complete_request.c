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
struct request {TYPE_1__* q; } ;
struct dm_rq_target_io {int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  mq_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_complete_request (struct request*) ; 
 int /*<<< orphan*/  blk_mq_complete_request (struct request*) ; 
 struct dm_rq_target_io* tio_from_request (struct request*) ; 

__attribute__((used)) static void dm_complete_request(struct request *rq, blk_status_t error)
{
	struct dm_rq_target_io *tio = tio_from_request(rq);

	tio->error = error;
	if (!rq->q->mq_ops)
		blk_complete_request(rq);
	else
		blk_mq_complete_request(rq);
}