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
struct rxe_mem {int va; int iova; int page_mask; int offset; int /*<<< orphan*/  page_shift; int /*<<< orphan*/  length; scalar_t__ nbuf; } ;
struct ib_mr {int iova; int page_size; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int ib_sg_to_pages (struct ib_mr*,struct scatterlist*,int,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  rxe_set_page ; 
 struct rxe_mem* to_rmr (struct ib_mr*) ; 

__attribute__((used)) static int rxe_map_mr_sg(struct ib_mr *ibmr, struct scatterlist *sg,
			 int sg_nents, unsigned int *sg_offset)
{
	struct rxe_mem *mr = to_rmr(ibmr);
	int n;

	mr->nbuf = 0;

	n = ib_sg_to_pages(ibmr, sg, sg_nents, sg_offset, rxe_set_page);

	mr->va = ibmr->iova;
	mr->iova = ibmr->iova;
	mr->length = ibmr->length;
	mr->page_shift = ilog2(ibmr->page_size);
	mr->page_mask = ibmr->page_size - 1;
	mr->offset = mr->iova & mr->page_mask;

	return n;
}