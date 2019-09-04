#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ib_mad_agent {int /*<<< orphan*/  port_num; int /*<<< orphan*/  qp; void* context; scalar_t__ snoop_handler; scalar_t__ recv_handler; struct ib_device* device; } ;
struct ib_mad_snoop_private {int mad_snoop_flags; int snoop_index; struct ib_mad_agent agent; int /*<<< orphan*/  refcount; int /*<<< orphan*/  comp; TYPE_1__* qp_info; } ;
struct ib_mad_port_private {TYPE_1__* qp_info; } ;
struct ib_device {int dummy; } ;
typedef  scalar_t__ ib_mad_snoop_handler ;
typedef  scalar_t__ ib_mad_recv_handler ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
struct TYPE_2__ {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct ib_mad_agent* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int get_spl_qp_index (int) ; 
 struct ib_mad_port_private* ib_get_mad_port (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_mad_agent_security_cleanup (struct ib_mad_agent*) ; 
 int ib_mad_agent_security_setup (struct ib_mad_agent*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ is_snooping_recvs (int) ; 
 scalar_t__ is_snooping_sends (int) ; 
 int /*<<< orphan*/  kfree (struct ib_mad_snoop_private*) ; 
 struct ib_mad_snoop_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int register_snoop_agent (TYPE_1__*,struct ib_mad_snoop_private*) ; 

struct ib_mad_agent *ib_register_mad_snoop(struct ib_device *device,
					   u8 port_num,
					   enum ib_qp_type qp_type,
					   int mad_snoop_flags,
					   ib_mad_snoop_handler snoop_handler,
					   ib_mad_recv_handler recv_handler,
					   void *context)
{
	struct ib_mad_port_private *port_priv;
	struct ib_mad_agent *ret;
	struct ib_mad_snoop_private *mad_snoop_priv;
	int qpn;
	int err;

	/* Validate parameters */
	if ((is_snooping_sends(mad_snoop_flags) && !snoop_handler) ||
	    (is_snooping_recvs(mad_snoop_flags) && !recv_handler)) {
		ret = ERR_PTR(-EINVAL);
		goto error1;
	}
	qpn = get_spl_qp_index(qp_type);
	if (qpn == -1) {
		ret = ERR_PTR(-EINVAL);
		goto error1;
	}
	port_priv = ib_get_mad_port(device, port_num);
	if (!port_priv) {
		ret = ERR_PTR(-ENODEV);
		goto error1;
	}
	/* Allocate structures */
	mad_snoop_priv = kzalloc(sizeof *mad_snoop_priv, GFP_KERNEL);
	if (!mad_snoop_priv) {
		ret = ERR_PTR(-ENOMEM);
		goto error1;
	}

	/* Now, fill in the various structures */
	mad_snoop_priv->qp_info = &port_priv->qp_info[qpn];
	mad_snoop_priv->agent.device = device;
	mad_snoop_priv->agent.recv_handler = recv_handler;
	mad_snoop_priv->agent.snoop_handler = snoop_handler;
	mad_snoop_priv->agent.context = context;
	mad_snoop_priv->agent.qp = port_priv->qp_info[qpn].qp;
	mad_snoop_priv->agent.port_num = port_num;
	mad_snoop_priv->mad_snoop_flags = mad_snoop_flags;
	init_completion(&mad_snoop_priv->comp);

	err = ib_mad_agent_security_setup(&mad_snoop_priv->agent, qp_type);
	if (err) {
		ret = ERR_PTR(err);
		goto error2;
	}

	mad_snoop_priv->snoop_index = register_snoop_agent(
						&port_priv->qp_info[qpn],
						mad_snoop_priv);
	if (mad_snoop_priv->snoop_index < 0) {
		ret = ERR_PTR(mad_snoop_priv->snoop_index);
		goto error3;
	}

	atomic_set(&mad_snoop_priv->refcount, 1);
	return &mad_snoop_priv->agent;
error3:
	ib_mad_agent_security_cleanup(&mad_snoop_priv->agent);
error2:
	kfree(mad_snoop_priv);
error1:
	return ret;
}