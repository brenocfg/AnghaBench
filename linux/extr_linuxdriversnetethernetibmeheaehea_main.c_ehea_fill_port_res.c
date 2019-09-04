#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ehea_qp_init_attr {scalar_t__ act_nr_rwqes_rq3; scalar_t__ act_nr_rwqes_rq2; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct ehea_port_res {TYPE_2__ rq1_skba; TYPE_1__* qp; } ;
struct TYPE_3__ {struct ehea_qp_init_attr init_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ehea_init_fill_rq1 (struct ehea_port_res*,int /*<<< orphan*/ ) ; 
 int ehea_refill_rq2 (struct ehea_port_res*,scalar_t__) ; 
 int ehea_refill_rq3 (struct ehea_port_res*,scalar_t__) ; 

__attribute__((used)) static int ehea_fill_port_res(struct ehea_port_res *pr)
{
	int ret;
	struct ehea_qp_init_attr *init_attr = &pr->qp->init_attr;

	ehea_init_fill_rq1(pr, pr->rq1_skba.len);

	ret = ehea_refill_rq2(pr, init_attr->act_nr_rwqes_rq2 - 1);

	ret |= ehea_refill_rq3(pr, init_attr->act_nr_rwqes_rq3 - 1);

	return ret;
}