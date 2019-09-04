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
struct TYPE_2__ {int /*<<< orphan*/  umem; int /*<<< orphan*/  pbl_tbl; int /*<<< orphan*/  pbl_info; } ;
struct qedr_srq {int /*<<< orphan*/  prod_umem; TYPE_1__ usrq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedr_free_pbl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedr_free_srq_user_params(struct qedr_srq *srq)
{
	qedr_free_pbl(srq->dev, &srq->usrq.pbl_info, srq->usrq.pbl_tbl);
	ib_umem_release(srq->usrq.umem);
	ib_umem_release(srq->prod_umem);
}