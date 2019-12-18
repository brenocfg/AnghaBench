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
struct scatterlist {int dummy; } ;
struct ib_block_iter {unsigned int __sg_nents; int /*<<< orphan*/  __pg_bit; struct scatterlist* __sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fls (unsigned long) ; 
 int /*<<< orphan*/  memset (struct ib_block_iter*,int /*<<< orphan*/ ,int) ; 

void __rdma_block_iter_start(struct ib_block_iter *biter,
			     struct scatterlist *sglist, unsigned int nents,
			     unsigned long pgsz)
{
	memset(biter, 0, sizeof(struct ib_block_iter));
	biter->__sg = sglist;
	biter->__sg_nents = nents;

	/* Driver provides best block size to use */
	biter->__pg_bit = __fls(pgsz);
}