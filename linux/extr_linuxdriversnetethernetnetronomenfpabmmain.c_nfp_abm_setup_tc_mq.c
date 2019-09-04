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
struct tc_mq_qopt_offload {int command; int /*<<< orphan*/  handle; } ;
struct nfp_abm_link {int /*<<< orphan*/  parent; int /*<<< orphan*/  total_queues; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  TC_H_ROOT ; 
#define  TC_MQ_CREATE 130 
#define  TC_MQ_DESTROY 129 
#define  TC_MQ_STATS 128 
 int nfp_abm_mq_stats (struct nfp_abm_link*,struct tc_mq_qopt_offload*) ; 
 int /*<<< orphan*/  nfp_abm_reset_root (struct net_device*,struct nfp_abm_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_abm_setup_tc_mq(struct net_device *netdev, struct nfp_abm_link *alink,
		    struct tc_mq_qopt_offload *opt)
{
	switch (opt->command) {
	case TC_MQ_CREATE:
		nfp_abm_reset_root(netdev, alink, opt->handle,
				   alink->total_queues);
		return 0;
	case TC_MQ_DESTROY:
		if (opt->handle == alink->parent)
			nfp_abm_reset_root(netdev, alink, TC_H_ROOT, 0);
		return 0;
	case TC_MQ_STATS:
		return nfp_abm_mq_stats(alink, opt);
	default:
		return -EOPNOTSUPP;
	}
}