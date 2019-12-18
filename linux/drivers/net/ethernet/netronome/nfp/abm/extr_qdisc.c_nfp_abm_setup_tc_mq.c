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
struct TYPE_2__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  child_handle; } ;
struct tc_mq_qopt_offload {int command; TYPE_1__ graft_params; int /*<<< orphan*/  handle; int /*<<< orphan*/  stats; } ;
struct nfp_abm_link {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_MQ_CREATE 131 
#define  TC_MQ_DESTROY 130 
#define  TC_MQ_GRAFT 129 
#define  TC_MQ_STATS 128 
 int nfp_abm_mq_create (struct net_device*,struct nfp_abm_link*,struct tc_mq_qopt_offload*) ; 
 int nfp_abm_mq_stats (struct nfp_abm_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_abm_qdisc_destroy (struct net_device*,struct nfp_abm_link*,int /*<<< orphan*/ ) ; 
 int nfp_abm_qdisc_graft (struct nfp_abm_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfp_abm_setup_tc_mq(struct net_device *netdev, struct nfp_abm_link *alink,
			struct tc_mq_qopt_offload *opt)
{
	switch (opt->command) {
	case TC_MQ_CREATE:
		return nfp_abm_mq_create(netdev, alink, opt);
	case TC_MQ_DESTROY:
		nfp_abm_qdisc_destroy(netdev, alink, opt->handle);
		return 0;
	case TC_MQ_STATS:
		return nfp_abm_mq_stats(alink, opt->handle, &opt->stats);
	case TC_MQ_GRAFT:
		return nfp_abm_qdisc_graft(alink, opt->handle,
					   opt->graft_params.child_handle,
					   opt->graft_params.queue);
	default:
		return -EOPNOTSUPP;
	}
}