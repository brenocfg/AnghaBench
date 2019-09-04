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
struct request {int cmd_flags; } ;

/* Variables and functions */
 unsigned long QUEUE_FLAG_FUA ; 
 unsigned long QUEUE_FLAG_WC ; 
 unsigned int REQ_FSEQ_DATA ; 
 unsigned int REQ_FSEQ_POSTFLUSH ; 
 unsigned int REQ_FSEQ_PREFLUSH ; 
 int REQ_FUA ; 
 int REQ_PREFLUSH ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 

__attribute__((used)) static unsigned int blk_flush_policy(unsigned long fflags, struct request *rq)
{
	unsigned int policy = 0;

	if (blk_rq_sectors(rq))
		policy |= REQ_FSEQ_DATA;

	if (fflags & (1UL << QUEUE_FLAG_WC)) {
		if (rq->cmd_flags & REQ_PREFLUSH)
			policy |= REQ_FSEQ_PREFLUSH;
		if (!(fflags & (1UL << QUEUE_FLAG_FUA)) &&
		    (rq->cmd_flags & REQ_FUA))
			policy |= REQ_FSEQ_POSTFLUSH;
	}
	return policy;
}