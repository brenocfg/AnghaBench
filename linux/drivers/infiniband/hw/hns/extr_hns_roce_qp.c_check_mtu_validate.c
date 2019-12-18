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
struct ib_qp_attr {int port_num; scalar_t__ path_mtu; } ;
struct hns_roce_qp {int port; } ;
struct TYPE_6__ {scalar_t__ max_mtu; } ;
struct TYPE_5__ {TYPE_1__** netdevs; } ;
struct hns_roce_dev {int /*<<< orphan*/  ib_dev; TYPE_3__ caps; TYPE_2__ iboe; } ;
typedef  enum ib_mtu { ____Placeholder_ib_mtu } ib_mtu ;
struct TYPE_4__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_MTU_2048 ; 
 scalar_t__ IB_MTU_256 ; 
 int IB_QP_PORT ; 
 int /*<<< orphan*/  ibdev_err (int /*<<< orphan*/ *,char*,int) ; 
 int iboe_get_mtu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_mtu_validate(struct hns_roce_dev *hr_dev,
			      struct hns_roce_qp *hr_qp,
			      struct ib_qp_attr *attr, int attr_mask)
{
	enum ib_mtu active_mtu;
	int p;

	p = attr_mask & IB_QP_PORT ? (attr->port_num - 1) : hr_qp->port;
	active_mtu = iboe_get_mtu(hr_dev->iboe.netdevs[p]->mtu);

	if ((hr_dev->caps.max_mtu >= IB_MTU_2048 &&
	    attr->path_mtu > hr_dev->caps.max_mtu) ||
	    attr->path_mtu < IB_MTU_256 || attr->path_mtu > active_mtu) {
		ibdev_err(&hr_dev->ib_dev,
			"attr path_mtu(%d)invalid while modify qp",
			attr->path_mtu);
		return -EINVAL;
	}

	return 0;
}