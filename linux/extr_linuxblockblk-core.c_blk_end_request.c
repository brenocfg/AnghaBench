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
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  mq_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int blk_end_bidi_request (struct request*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

bool blk_end_request(struct request *rq, blk_status_t error,
		unsigned int nr_bytes)
{
	WARN_ON_ONCE(rq->q->mq_ops);
	return blk_end_bidi_request(rq, error, nr_bytes, 0);
}