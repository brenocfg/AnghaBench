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
struct qedr_qp {int /*<<< orphan*/  refcnt; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct qedr_qp* get_qedr_qp (struct ib_qp*) ; 

void qedr_iw_qp_add_ref(struct ib_qp *ibqp)
{
	struct qedr_qp *qp = get_qedr_qp(ibqp);

	atomic_inc(&qp->refcnt);
}