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
struct srpt_rdma_ch {int /*<<< orphan*/  pkey; TYPE_2__* sport; int /*<<< orphan*/  using_rdma_cm; } ;
struct ib_qp_attr {int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  port_num; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  qp_state; } ;
struct ib_qp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; TYPE_1__* sdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_ACCESS_LOCAL_WRITE ; 
 int /*<<< orphan*/  IB_QPS_INIT ; 
 int IB_QP_ACCESS_FLAGS ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_PORT ; 
 int IB_QP_STATE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int ib_find_cached_pkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ib_modify_qp (struct ib_qp*,struct ib_qp_attr*,int) ; 
 int /*<<< orphan*/  kfree (struct ib_qp_attr*) ; 
 struct ib_qp_attr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int srpt_init_ch_qp(struct srpt_rdma_ch *ch, struct ib_qp *qp)
{
	struct ib_qp_attr *attr;
	int ret;

	WARN_ON_ONCE(ch->using_rdma_cm);

	attr = kzalloc(sizeof(*attr), GFP_KERNEL);
	if (!attr)
		return -ENOMEM;

	attr->qp_state = IB_QPS_INIT;
	attr->qp_access_flags = IB_ACCESS_LOCAL_WRITE;
	attr->port_num = ch->sport->port;

	ret = ib_find_cached_pkey(ch->sport->sdev->device, ch->sport->port,
				  ch->pkey, &attr->pkey_index);
	if (ret < 0)
		pr_err("Translating pkey %#x failed (%d) - using index 0\n",
		       ch->pkey, ret);

	ret = ib_modify_qp(qp, attr,
			   IB_QP_STATE | IB_QP_ACCESS_FLAGS | IB_QP_PORT |
			   IB_QP_PKEY_INDEX);

	kfree(attr);
	return ret;
}