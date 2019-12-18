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
struct bnxt_qplib_res {int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int max_elements; } ;
struct bnxt_qplib_frpl {int max_pg_ptrs; TYPE_1__ hwq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HWQ_TYPE_CTX ; 
 int MAX_PBL_LVL_1_PGS ; 
 int MAX_PBL_LVL_1_PGS_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int bnxt_qplib_alloc_init_hwq (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int roundup_pow_of_two (int) ; 

int bnxt_qplib_alloc_fast_reg_page_list(struct bnxt_qplib_res *res,
					struct bnxt_qplib_frpl *frpl,
					int max_pg_ptrs)
{
	int pg_ptrs, pages, rc;

	/* Re-calculate the max to fit the HWQ allocation model */
	pg_ptrs = roundup_pow_of_two(max_pg_ptrs);
	pages = pg_ptrs >> MAX_PBL_LVL_1_PGS_SHIFT;
	if (!pages)
		pages++;

	if (pages > MAX_PBL_LVL_1_PGS)
		return -ENOMEM;

	frpl->hwq.max_elements = pages;
	rc = bnxt_qplib_alloc_init_hwq(res->pdev, &frpl->hwq, NULL,
				       &frpl->hwq.max_elements, PAGE_SIZE, 0,
				       PAGE_SIZE, HWQ_TYPE_CTX);
	if (!rc)
		frpl->max_pg_ptrs = pg_ptrs;

	return rc;
}