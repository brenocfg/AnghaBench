#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ib_mad_snoop_private {size_t snoop_index; int /*<<< orphan*/  agent; int /*<<< orphan*/  comp; struct ib_mad_qp_info* qp_info; } ;
struct ib_mad_qp_info {int /*<<< orphan*/  snoop_lock; int /*<<< orphan*/  snoop_count; int /*<<< orphan*/ ** snoop_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deref_snoop_agent (struct ib_mad_snoop_private*) ; 
 int /*<<< orphan*/  ib_mad_agent_security_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_mad_snoop_private*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unregister_mad_snoop(struct ib_mad_snoop_private *mad_snoop_priv)
{
	struct ib_mad_qp_info *qp_info;
	unsigned long flags;

	qp_info = mad_snoop_priv->qp_info;
	spin_lock_irqsave(&qp_info->snoop_lock, flags);
	qp_info->snoop_table[mad_snoop_priv->snoop_index] = NULL;
	atomic_dec(&qp_info->snoop_count);
	spin_unlock_irqrestore(&qp_info->snoop_lock, flags);

	deref_snoop_agent(mad_snoop_priv);
	wait_for_completion(&mad_snoop_priv->comp);

	ib_mad_agent_security_cleanup(&mad_snoop_priv->agent);

	kfree(mad_snoop_priv);
}