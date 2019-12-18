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
struct ib_qp_security {int /*<<< orphan*/  shared_qp_list; TYPE_1__* qp; } ;
struct ib_qp {TYPE_2__* qp_sec; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {struct ib_qp* real_qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_qp_security (struct ib_qp_security*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ib_close_shared_qp_security(struct ib_qp_security *sec)
{
	struct ib_qp *real_qp = sec->qp->real_qp;

	mutex_lock(&real_qp->qp_sec->mutex);
	list_del(&sec->shared_qp_list);
	mutex_unlock(&real_qp->qp_sec->mutex);

	destroy_qp_security(sec);
}