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
struct ib_mad_agent {int /*<<< orphan*/  lsm_nb; scalar_t__ lsm_nb_reg; int /*<<< orphan*/  security; int /*<<< orphan*/  port_num; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdma_protocol_ib (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_ib_free_security (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_lsm_notifier (int /*<<< orphan*/ *) ; 

void ib_mad_agent_security_cleanup(struct ib_mad_agent *agent)
{
	if (!rdma_protocol_ib(agent->device, agent->port_num))
		return;

	security_ib_free_security(agent->security);
	if (agent->lsm_nb_reg)
		unregister_lsm_notifier(&agent->lsm_nb);
}