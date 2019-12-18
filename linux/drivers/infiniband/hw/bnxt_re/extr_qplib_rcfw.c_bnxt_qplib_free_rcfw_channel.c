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
struct bnxt_qplib_rcfw {int /*<<< orphan*/ * pdev; int /*<<< orphan*/  creq; int /*<<< orphan*/  cmdq; int /*<<< orphan*/  crsqe_tbl; int /*<<< orphan*/  qp_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_qplib_free_hwq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void bnxt_qplib_free_rcfw_channel(struct bnxt_qplib_rcfw *rcfw)
{
	kfree(rcfw->qp_tbl);
	kfree(rcfw->crsqe_tbl);
	bnxt_qplib_free_hwq(rcfw->pdev, &rcfw->cmdq);
	bnxt_qplib_free_hwq(rcfw->pdev, &rcfw->creq);
	rcfw->pdev = NULL;
}