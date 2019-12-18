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
struct ib_mad_agent {int /*<<< orphan*/  security; int /*<<< orphan*/  mad_agent_sec_list; TYPE_1__* qp; int /*<<< orphan*/  port_num; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {scalar_t__ qp_type; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_SMI ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mad_agent_list_lock ; 
 int /*<<< orphan*/  rdma_protocol_ib (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_ib_free_security (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ib_mad_agent_security_cleanup(struct ib_mad_agent *agent)
{
	if (!rdma_protocol_ib(agent->device, agent->port_num))
		return;

	if (agent->qp->qp_type == IB_QPT_SMI) {
		spin_lock(&mad_agent_list_lock);
		list_del(&agent->mad_agent_sec_list);
		spin_unlock(&mad_agent_list_lock);
	}

	security_ib_free_security(agent->security);
}