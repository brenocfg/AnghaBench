#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ max; } ;
struct TYPE_4__ {int /*<<< orphan*/ * rcfw; TYPE_3__ dpi_tbl; } ;
struct bnxt_re_dev {TYPE_1__ qplib_res; int /*<<< orphan*/  dpi_privileged; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_qplib_dealloc_dpi (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_qplib_free_res (TYPE_1__*) ; 
 int /*<<< orphan*/  bnxt_re_free_nq_res (struct bnxt_re_dev*) ; 

__attribute__((used)) static void bnxt_re_free_res(struct bnxt_re_dev *rdev)
{
	bnxt_re_free_nq_res(rdev);

	if (rdev->qplib_res.dpi_tbl.max) {
		bnxt_qplib_dealloc_dpi(&rdev->qplib_res,
				       &rdev->qplib_res.dpi_tbl,
				       &rdev->dpi_privileged);
	}
	if (rdev->qplib_res.rcfw) {
		bnxt_qplib_free_res(&rdev->qplib_res);
		rdev->qplib_res.rcfw = NULL;
	}
}