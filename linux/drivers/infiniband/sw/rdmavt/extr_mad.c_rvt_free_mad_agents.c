#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rvt_ibport {TYPE_1__* sm_ah; struct ib_mad_agent* send_agent; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* notify_free_mad_agent ) (struct rvt_dev_info*,int) ;} ;
struct TYPE_6__ {int nports; } ;
struct rvt_dev_info {TYPE_2__ driver_f; struct rvt_ibport** ports; TYPE_3__ dparms; } ;
struct ib_mad_agent {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ibah; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_DESTROY_AH_SLEEPABLE ; 
 int /*<<< orphan*/  ib_unregister_mad_agent (struct ib_mad_agent*) ; 
 int /*<<< orphan*/  rdma_destroy_ah (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rvt_dev_info*,int) ; 

void rvt_free_mad_agents(struct rvt_dev_info *rdi)
{
	struct ib_mad_agent *agent;
	struct rvt_ibport *rvp;
	int p;

	for (p = 0; p < rdi->dparms.nports; p++) {
		rvp = rdi->ports[p];
		if (rvp->send_agent) {
			agent = rvp->send_agent;
			rvp->send_agent = NULL;
			ib_unregister_mad_agent(agent);
		}
		if (rvp->sm_ah) {
			rdma_destroy_ah(&rvp->sm_ah->ibah,
					RDMA_DESTROY_AH_SLEEPABLE);
			rvp->sm_ah = NULL;
		}

		if (rdi->driver_f.notify_free_mad_agent)
			rdi->driver_f.notify_free_mad_agent(rdi, p);
	}
}