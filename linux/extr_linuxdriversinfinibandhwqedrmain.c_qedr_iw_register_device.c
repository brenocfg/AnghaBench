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
struct TYPE_4__ {TYPE_3__* iwcm; int /*<<< orphan*/  get_port_immutable; int /*<<< orphan*/  query_gid; int /*<<< orphan*/  node_type; } ;
struct qedr_dev {TYPE_2__* ndev; TYPE_1__ ibdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  ifname; int /*<<< orphan*/  get_qp; int /*<<< orphan*/  rem_ref; int /*<<< orphan*/  add_ref; int /*<<< orphan*/  destroy_listen; int /*<<< orphan*/  create_listen; int /*<<< orphan*/  reject; int /*<<< orphan*/  accept; int /*<<< orphan*/  connect; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RDMA_NODE_RNIC ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedr_iw_accept ; 
 int /*<<< orphan*/  qedr_iw_connect ; 
 int /*<<< orphan*/  qedr_iw_create_listen ; 
 int /*<<< orphan*/  qedr_iw_destroy_listen ; 
 int /*<<< orphan*/  qedr_iw_get_qp ; 
 int /*<<< orphan*/  qedr_iw_port_immutable ; 
 int /*<<< orphan*/  qedr_iw_qp_add_ref ; 
 int /*<<< orphan*/  qedr_iw_qp_rem_ref ; 
 int /*<<< orphan*/  qedr_iw_query_gid ; 
 int /*<<< orphan*/  qedr_iw_reject ; 

__attribute__((used)) static int qedr_iw_register_device(struct qedr_dev *dev)
{
	dev->ibdev.node_type = RDMA_NODE_RNIC;
	dev->ibdev.query_gid = qedr_iw_query_gid;

	dev->ibdev.get_port_immutable = qedr_iw_port_immutable;

	dev->ibdev.iwcm = kzalloc(sizeof(*dev->ibdev.iwcm), GFP_KERNEL);
	if (!dev->ibdev.iwcm)
		return -ENOMEM;

	dev->ibdev.iwcm->connect = qedr_iw_connect;
	dev->ibdev.iwcm->accept = qedr_iw_accept;
	dev->ibdev.iwcm->reject = qedr_iw_reject;
	dev->ibdev.iwcm->create_listen = qedr_iw_create_listen;
	dev->ibdev.iwcm->destroy_listen = qedr_iw_destroy_listen;
	dev->ibdev.iwcm->add_ref = qedr_iw_qp_add_ref;
	dev->ibdev.iwcm->rem_ref = qedr_iw_qp_rem_ref;
	dev->ibdev.iwcm->get_qp = qedr_iw_get_qp;

	memcpy(dev->ibdev.iwcm->ifname,
	       dev->ndev->name, sizeof(dev->ibdev.iwcm->ifname));

	return 0;
}