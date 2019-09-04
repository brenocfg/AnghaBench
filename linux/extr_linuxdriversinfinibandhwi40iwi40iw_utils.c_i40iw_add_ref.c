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
struct ib_qp {int dummy; } ;
struct i40iw_qp {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

void i40iw_add_ref(struct ib_qp *ibqp)
{
	struct i40iw_qp *iwqp = (struct i40iw_qp *)ibqp;

	atomic_inc(&iwqp->refcount);
}