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
struct scatterlist {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  page_shift; scalar_t__ length; } ;
struct rvt_mr {TYPE_1__ mr; } ;
struct ib_mr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int ib_sg_to_pages (struct ib_mr*,struct scatterlist*,int,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_set_page ; 
 struct rvt_mr* to_imr (struct ib_mr*) ; 

int rvt_map_mr_sg(struct ib_mr *ibmr, struct scatterlist *sg,
		  int sg_nents, unsigned int *sg_offset)
{
	struct rvt_mr *mr = to_imr(ibmr);

	mr->mr.length = 0;
	mr->mr.page_shift = PAGE_SHIFT;
	return ib_sg_to_pages(ibmr, sg, sg_nents, sg_offset,
			      rvt_set_page);
}