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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__ port_num; } ;
struct usnic_transport_spec {int trans_type; TYPE_1__ usnic_roce; } ;
struct TYPE_4__ {scalar_t__ port_num; } ;
struct usnic_ib_qp_grp_flow {int trans_type; struct usnic_ib_qp_grp* qp_grp; TYPE_2__ usnic_roce; struct usnic_fwd_flow* flow; } ;
struct usnic_ib_qp_grp {int /*<<< orphan*/  ufdev; } ;
struct usnic_fwd_flow {int dummy; } ;
struct usnic_filter_action {int dummy; } ;
struct filter {int dummy; } ;
typedef  enum usnic_transport_type { ____Placeholder_usnic_transport_type } usnic_transport_type ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct usnic_ib_qp_grp_flow* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR_OR_NULL (struct usnic_fwd_flow*) ; 
 int PTR_ERR (struct usnic_fwd_flow*) ; 
 int init_filter_action (struct usnic_ib_qp_grp*,struct usnic_filter_action*) ; 
 struct usnic_ib_qp_grp_flow* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct usnic_fwd_flow* usnic_fwd_alloc_flow (int /*<<< orphan*/ ,struct filter*,struct usnic_filter_action*) ; 
 int /*<<< orphan*/  usnic_fwd_dealloc_flow (struct usnic_fwd_flow*) ; 
 int /*<<< orphan*/  usnic_fwd_init_usnic_filter (struct filter*,scalar_t__) ; 
 scalar_t__ usnic_transport_rsrv_port (int,scalar_t__) ; 
 int /*<<< orphan*/  usnic_transport_unrsrv_port (int,scalar_t__) ; 

__attribute__((used)) static struct usnic_ib_qp_grp_flow*
create_roce_custom_flow(struct usnic_ib_qp_grp *qp_grp,
			struct usnic_transport_spec *trans_spec)
{
	uint16_t port_num;
	int err;
	struct filter filter;
	struct usnic_filter_action uaction;
	struct usnic_ib_qp_grp_flow *qp_flow;
	struct usnic_fwd_flow *flow;
	enum usnic_transport_type trans_type;

	trans_type = trans_spec->trans_type;
	port_num = trans_spec->usnic_roce.port_num;

	/* Reserve Port */
	port_num = usnic_transport_rsrv_port(trans_type, port_num);
	if (port_num == 0)
		return ERR_PTR(-EINVAL);

	/* Create Flow */
	usnic_fwd_init_usnic_filter(&filter, port_num);
	err = init_filter_action(qp_grp, &uaction);
	if (err)
		goto out_unreserve_port;

	flow = usnic_fwd_alloc_flow(qp_grp->ufdev, &filter, &uaction);
	if (IS_ERR_OR_NULL(flow)) {
		err = flow ? PTR_ERR(flow) : -EFAULT;
		goto out_unreserve_port;
	}

	/* Create Flow Handle */
	qp_flow = kzalloc(sizeof(*qp_flow), GFP_ATOMIC);
	if (!qp_flow) {
		err = -ENOMEM;
		goto out_dealloc_flow;
	}
	qp_flow->flow = flow;
	qp_flow->trans_type = trans_type;
	qp_flow->usnic_roce.port_num = port_num;
	qp_flow->qp_grp = qp_grp;
	return qp_flow;

out_dealloc_flow:
	usnic_fwd_dealloc_flow(flow);
out_unreserve_port:
	usnic_transport_unrsrv_port(trans_type, port_num);
	return ERR_PTR(err);
}