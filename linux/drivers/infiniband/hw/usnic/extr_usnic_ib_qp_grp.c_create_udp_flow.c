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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int sock_fd; } ;
struct usnic_transport_spec {int trans_type; TYPE_1__ udp; } ;
struct TYPE_4__ {struct usnic_fwd_flow* sock; } ;
struct usnic_ib_qp_grp_flow {int trans_type; struct usnic_ib_qp_grp* qp_grp; TYPE_2__ udp; struct usnic_fwd_flow* flow; } ;
struct usnic_ib_qp_grp {int /*<<< orphan*/  ufdev; } ;
struct usnic_fwd_flow {int dummy; } ;
struct usnic_filter_action {int dummy; } ;
typedef  struct usnic_fwd_flow socket ;
struct filter {int dummy; } ;
typedef  enum usnic_transport_type { ____Placeholder_usnic_transport_type } usnic_transport_type ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int EPERM ; 
 struct usnic_ib_qp_grp_flow* ERR_CAST (struct usnic_fwd_flow*) ; 
 struct usnic_ib_qp_grp_flow* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IPPROTO_UDP ; 
 scalar_t__ IS_ERR_OR_NULL (struct usnic_fwd_flow*) ; 
 int PTR_ERR (struct usnic_fwd_flow*) ; 
 int init_filter_action (struct usnic_ib_qp_grp*,struct usnic_filter_action*) ; 
 struct usnic_ib_qp_grp_flow* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_err (char*,int) ; 
 struct usnic_fwd_flow* usnic_fwd_alloc_flow (int /*<<< orphan*/ ,struct filter*,struct usnic_filter_action*) ; 
 int /*<<< orphan*/  usnic_fwd_dealloc_flow (struct usnic_fwd_flow*) ; 
 int /*<<< orphan*/  usnic_fwd_init_udp_filter (struct filter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usnic_fwd_flow* usnic_transport_get_socket (int) ; 
 int /*<<< orphan*/  usnic_transport_put_socket (struct usnic_fwd_flow*) ; 
 int usnic_transport_sock_get_addr (struct usnic_fwd_flow*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct usnic_ib_qp_grp_flow*
create_udp_flow(struct usnic_ib_qp_grp *qp_grp,
		struct usnic_transport_spec *trans_spec)
{
	struct socket *sock;
	int sock_fd;
	int err;
	struct filter filter;
	struct usnic_filter_action uaction;
	struct usnic_ib_qp_grp_flow *qp_flow;
	struct usnic_fwd_flow *flow;
	enum usnic_transport_type trans_type;
	uint32_t addr;
	uint16_t port_num;
	int proto;

	trans_type = trans_spec->trans_type;
	sock_fd = trans_spec->udp.sock_fd;

	/* Get and check socket */
	sock = usnic_transport_get_socket(sock_fd);
	if (IS_ERR_OR_NULL(sock))
		return ERR_CAST(sock);

	err = usnic_transport_sock_get_addr(sock, &proto, &addr, &port_num);
	if (err)
		goto out_put_sock;

	if (proto != IPPROTO_UDP) {
		usnic_err("Protocol for fd %d is not UDP", sock_fd);
		err = -EPERM;
		goto out_put_sock;
	}

	/* Create flow */
	usnic_fwd_init_udp_filter(&filter, addr, port_num);
	err = init_filter_action(qp_grp, &uaction);
	if (err)
		goto out_put_sock;

	flow = usnic_fwd_alloc_flow(qp_grp->ufdev, &filter, &uaction);
	if (IS_ERR_OR_NULL(flow)) {
		err = flow ? PTR_ERR(flow) : -EFAULT;
		goto out_put_sock;
	}

	/* Create qp_flow */
	qp_flow = kzalloc(sizeof(*qp_flow), GFP_ATOMIC);
	if (!qp_flow) {
		err = -ENOMEM;
		goto out_dealloc_flow;
	}
	qp_flow->flow = flow;
	qp_flow->trans_type = trans_type;
	qp_flow->udp.sock = sock;
	qp_flow->qp_grp = qp_grp;
	return qp_flow;

out_dealloc_flow:
	usnic_fwd_dealloc_flow(flow);
out_put_sock:
	usnic_transport_put_socket(sock);
	return ERR_PTR(err);
}