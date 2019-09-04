#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pkey; } ;
struct srp_target_port {TYPE_3__* srp_host; TYPE_2__ ib_cm; } ;
struct ib_qp_attr {int qp_access_flags; int /*<<< orphan*/  port_num; int /*<<< orphan*/  qp_state; int /*<<< orphan*/  pkey_index; } ;
struct ib_qp {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  port; TYPE_1__* srp_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int /*<<< orphan*/  IB_QPS_INIT ; 
 int IB_QP_ACCESS_FLAGS ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_PORT ; 
 int IB_QP_STATE ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int ib_find_cached_pkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ib_modify_qp (struct ib_qp*,struct ib_qp_attr*,int) ; 
 int /*<<< orphan*/  kfree (struct ib_qp_attr*) ; 
 struct ib_qp_attr* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int srp_init_ib_qp(struct srp_target_port *target,
			  struct ib_qp *qp)
{
	struct ib_qp_attr *attr;
	int ret;

	attr = kmalloc(sizeof *attr, GFP_KERNEL);
	if (!attr)
		return -ENOMEM;

	ret = ib_find_cached_pkey(target->srp_host->srp_dev->dev,
				  target->srp_host->port,
				  be16_to_cpu(target->ib_cm.pkey),
				  &attr->pkey_index);
	if (ret)
		goto out;

	attr->qp_state        = IB_QPS_INIT;
	attr->qp_access_flags = (IB_ACCESS_REMOTE_READ |
				    IB_ACCESS_REMOTE_WRITE);
	attr->port_num        = target->srp_host->port;

	ret = ib_modify_qp(qp, attr,
			   IB_QP_STATE		|
			   IB_QP_PKEY_INDEX	|
			   IB_QP_ACCESS_FLAGS	|
			   IB_QP_PORT);

out:
	kfree(attr);
	return ret;
}