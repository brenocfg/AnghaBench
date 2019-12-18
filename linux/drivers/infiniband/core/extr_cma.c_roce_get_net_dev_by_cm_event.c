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
struct net_device {int dummy; } ;
struct ib_gid_attr {int dummy; } ;
struct TYPE_5__ {struct ib_gid_attr* sgid_attr; } ;
struct TYPE_4__ {struct ib_gid_attr* ppath_sgid_attr; } ;
struct TYPE_6__ {TYPE_2__ sidr_req_rcvd; TYPE_1__ req_rcvd; } ;
struct ib_cm_event {scalar_t__ event; TYPE_3__ param; } ;

/* Variables and functions */
 scalar_t__ IB_CM_REQ_RECEIVED ; 
 scalar_t__ IB_CM_SIDR_REQ_RECEIVED ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct net_device* rdma_read_gid_attr_ndev_rcu (struct ib_gid_attr const*) ; 

__attribute__((used)) static struct net_device *
roce_get_net_dev_by_cm_event(const struct ib_cm_event *ib_event)
{
	const struct ib_gid_attr *sgid_attr = NULL;
	struct net_device *ndev;

	if (ib_event->event == IB_CM_REQ_RECEIVED)
		sgid_attr = ib_event->param.req_rcvd.ppath_sgid_attr;
	else if (ib_event->event == IB_CM_SIDR_REQ_RECEIVED)
		sgid_attr = ib_event->param.sidr_req_rcvd.sgid_attr;

	if (!sgid_attr)
		return NULL;

	rcu_read_lock();
	ndev = rdma_read_gid_attr_ndev_rcu(sgid_attr);
	if (IS_ERR(ndev))
		ndev = NULL;
	else
		dev_hold(ndev);
	rcu_read_unlock();
	return ndev;
}