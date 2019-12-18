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
struct ib_mad_port_private {int /*<<< orphan*/  wq; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  hi_tid; } ;
struct ib_mad_agent_private {int /*<<< orphan*/  reg_req; TYPE_2__ agent; int /*<<< orphan*/  comp; int /*<<< orphan*/  timed_work; TYPE_1__* qp_info; } ;
struct TYPE_3__ {struct ib_mad_port_private* port_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_mads (struct ib_mad_agent_private*) ; 
 int /*<<< orphan*/  deref_mad_agent (struct ib_mad_agent_private*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_cancel_rmpp_recvs (struct ib_mad_agent_private*) ; 
 int /*<<< orphan*/  ib_mad_agent_security_cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  ib_mad_clients ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct ib_mad_agent_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  remove_mad_reg_req (struct ib_mad_agent_private*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ib_mad_unregister_agent (struct ib_mad_agent_private*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unregister_mad_agent(struct ib_mad_agent_private *mad_agent_priv)
{
	struct ib_mad_port_private *port_priv;

	/* Note that we could still be handling received MADs */
	trace_ib_mad_unregister_agent(mad_agent_priv);

	/*
	 * Canceling all sends results in dropping received response
	 * MADs, preventing us from queuing additional work
	 */
	cancel_mads(mad_agent_priv);
	port_priv = mad_agent_priv->qp_info->port_priv;
	cancel_delayed_work(&mad_agent_priv->timed_work);

	spin_lock_irq(&port_priv->reg_lock);
	remove_mad_reg_req(mad_agent_priv);
	spin_unlock_irq(&port_priv->reg_lock);
	xa_erase(&ib_mad_clients, mad_agent_priv->agent.hi_tid);

	flush_workqueue(port_priv->wq);
	ib_cancel_rmpp_recvs(mad_agent_priv);

	deref_mad_agent(mad_agent_priv);
	wait_for_completion(&mad_agent_priv->comp);

	ib_mad_agent_security_cleanup(&mad_agent_priv->agent);

	kfree(mad_agent_priv->reg_req);
	kfree_rcu(mad_agent_priv, rcu);
}