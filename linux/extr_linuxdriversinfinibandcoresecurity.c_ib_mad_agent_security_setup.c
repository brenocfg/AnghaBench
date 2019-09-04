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
struct TYPE_3__ {int /*<<< orphan*/  notifier_call; } ;
struct ib_mad_agent {int smp_allowed; int lsm_nb_reg; TYPE_1__ lsm_nb; int /*<<< orphan*/  port_num; TYPE_2__* device; int /*<<< orphan*/  security; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int IB_QPT_SMI ; 
 int /*<<< orphan*/  ib_mad_agent_security_change ; 
 int /*<<< orphan*/  rdma_protocol_ib (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int register_lsm_notifier (TYPE_1__*) ; 
 int security_ib_alloc_security (int /*<<< orphan*/ *) ; 
 int security_ib_endport_manage_subnet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ib_mad_agent_security_setup(struct ib_mad_agent *agent,
				enum ib_qp_type qp_type)
{
	int ret;

	if (!rdma_protocol_ib(agent->device, agent->port_num))
		return 0;

	ret = security_ib_alloc_security(&agent->security);
	if (ret)
		return ret;

	if (qp_type != IB_QPT_SMI)
		return 0;

	ret = security_ib_endport_manage_subnet(agent->security,
						agent->device->name,
						agent->port_num);
	if (ret)
		return ret;

	agent->lsm_nb.notifier_call = ib_mad_agent_security_change;
	ret = register_lsm_notifier(&agent->lsm_nb);
	if (ret)
		return ret;

	agent->smp_allowed = true;
	agent->lsm_nb_reg = true;
	return 0;
}