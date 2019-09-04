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
struct qp_list {int /*<<< orphan*/  idx; struct c4iw_qp** qps; } ;
struct c4iw_qp {int /*<<< orphan*/  ibqp; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_qp_add_ref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_and_ref_qp(int id, void *p, void *data)
{
	struct qp_list *qp_listp = data;
	struct c4iw_qp *qp = p;

	c4iw_qp_add_ref(&qp->ibqp);
	qp_listp->qps[qp_listp->idx++] = qp;
	return 0;
}