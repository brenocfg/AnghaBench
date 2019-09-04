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
struct request {int dummy; } ;
struct bfq_queue {int wr_coeff; } ;

/* Variables and functions */
 unsigned long bfq_async_charge_factor ; 
 scalar_t__ bfq_bfqq_sync (struct bfq_queue*) ; 
 unsigned long blk_rq_sectors (struct request*) ; 

__attribute__((used)) static unsigned long bfq_serv_to_charge(struct request *rq,
					struct bfq_queue *bfqq)
{
	if (bfq_bfqq_sync(bfqq) || bfqq->wr_coeff > 1)
		return blk_rq_sectors(rq);

	return blk_rq_sectors(rq) * bfq_async_charge_factor;
}