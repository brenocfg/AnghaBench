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
struct ib_cq {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (struct ib_cq*,int /*<<< orphan*/ ) ;} ;
struct hns_roce_cq {struct ib_cq ib_cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ib_cq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_ib_cq_comp(struct hns_roce_cq *hr_cq)
{
	struct ib_cq *ibcq = &hr_cq->ib_cq;

	ibcq->comp_handler(ibcq, ibcq->cq_context);
}