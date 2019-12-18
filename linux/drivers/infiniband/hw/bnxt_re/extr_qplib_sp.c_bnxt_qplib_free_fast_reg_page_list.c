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
struct bnxt_qplib_res {int /*<<< orphan*/  pdev; } ;
struct bnxt_qplib_frpl {int /*<<< orphan*/  hwq; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_qplib_free_hwq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bnxt_qplib_free_fast_reg_page_list(struct bnxt_qplib_res *res,
				       struct bnxt_qplib_frpl *frpl)
{
	bnxt_qplib_free_hwq(res->pdev, &frpl->hwq);
	return 0;
}