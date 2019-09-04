#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ib_qp {TYPE_1__* qp_sec; struct ib_qp* real_qp; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  shared_qp_list; int /*<<< orphan*/  ports_pkeys; } ;

/* Variables and functions */
 int check_qp_port_pkey_settings (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  destroy_qp_security (TYPE_1__*) ; 
 int ib_create_qp_security (struct ib_qp*,struct ib_device*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ib_open_shared_qp_security(struct ib_qp *qp, struct ib_device *dev)
{
	struct ib_qp *real_qp = qp->real_qp;
	int ret;

	ret = ib_create_qp_security(qp, dev);

	if (ret)
		return ret;

	if (!qp->qp_sec)
		return 0;

	mutex_lock(&real_qp->qp_sec->mutex);
	ret = check_qp_port_pkey_settings(real_qp->qp_sec->ports_pkeys,
					  qp->qp_sec);

	if (ret)
		goto ret;

	if (qp != real_qp)
		list_add(&qp->qp_sec->shared_qp_list,
			 &real_qp->qp_sec->shared_qp_list);
ret:
	mutex_unlock(&real_qp->qp_sec->mutex);
	if (ret)
		destroy_qp_security(qp->qp_sec);

	return ret;
}