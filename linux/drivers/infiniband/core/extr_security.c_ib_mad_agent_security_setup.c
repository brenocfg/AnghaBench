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
struct ib_mad_agent {int /*<<< orphan*/  security; int /*<<< orphan*/  mad_agent_sec_list; int /*<<< orphan*/  smp_allowed; int /*<<< orphan*/  port_num; TYPE_1__* device; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IB_QPT_SMI ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mad_agent_list ; 
 int /*<<< orphan*/  mad_agent_list_lock ; 
 int /*<<< orphan*/  rdma_protocol_ib (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int security_ib_alloc_security (int /*<<< orphan*/ *) ; 
 int security_ib_endport_manage_subnet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_ib_free_security (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ib_mad_agent_security_setup(struct ib_mad_agent *agent,
				enum ib_qp_type qp_type)
{
	int ret;

	if (!rdma_protocol_ib(agent->device, agent->port_num))
		return 0;

	INIT_LIST_HEAD(&agent->mad_agent_sec_list);

	ret = security_ib_alloc_security(&agent->security);
	if (ret)
		return ret;

	if (qp_type != IB_QPT_SMI)
		return 0;

	spin_lock(&mad_agent_list_lock);
	ret = security_ib_endport_manage_subnet(agent->security,
						dev_name(&agent->device->dev),
						agent->port_num);
	if (ret)
		goto free_security;

	WRITE_ONCE(agent->smp_allowed, true);
	list_add(&agent->mad_agent_sec_list, &mad_agent_list);
	spin_unlock(&mad_agent_list_lock);
	return 0;

free_security:
	spin_unlock(&mad_agent_list_lock);
	security_ib_free_security(agent->security);
	return ret;
}