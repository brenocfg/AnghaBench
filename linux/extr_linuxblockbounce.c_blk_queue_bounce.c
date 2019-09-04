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
struct TYPE_2__ {scalar_t__ bounce_pfn; } ;
struct request_queue {int bounce_gfp; TYPE_1__ limits; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  mempool_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int GFP_DMA ; 
 int /*<<< orphan*/  __blk_queue_bounce (struct request_queue*,struct bio**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_has_data (struct bio*) ; 
 scalar_t__ blk_max_pfn ; 
 int /*<<< orphan*/  isa_page_pool ; 
 int /*<<< orphan*/  mempool_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_pool ; 

void blk_queue_bounce(struct request_queue *q, struct bio **bio_orig)
{
	mempool_t *pool;

	/*
	 * Data-less bio, nothing to bounce
	 */
	if (!bio_has_data(*bio_orig))
		return;

	/*
	 * for non-isa bounce case, just check if the bounce pfn is equal
	 * to or bigger than the highest pfn in the system -- in that case,
	 * don't waste time iterating over bio segments
	 */
	if (!(q->bounce_gfp & GFP_DMA)) {
		if (q->limits.bounce_pfn >= blk_max_pfn)
			return;
		pool = &page_pool;
	} else {
		BUG_ON(!mempool_initialized(&isa_page_pool));
		pool = &isa_page_pool;
	}

	/*
	 * slow path
	 */
	__blk_queue_bounce(q, bio_orig, pool);
}