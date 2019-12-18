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
struct tc_gred_qopt_offload {int command; int /*<<< orphan*/  stats; int /*<<< orphan*/  handle; } ;
struct nfp_abm_link {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_GRED_DESTROY 130 
#define  TC_GRED_REPLACE 129 
#define  TC_GRED_STATS 128 
 int nfp_abm_gred_replace (struct net_device*,struct nfp_abm_link*,struct tc_gred_qopt_offload*) ; 
 int nfp_abm_gred_stats (struct nfp_abm_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_abm_qdisc_destroy (struct net_device*,struct nfp_abm_link*,int /*<<< orphan*/ ) ; 

int nfp_abm_setup_tc_gred(struct net_device *netdev, struct nfp_abm_link *alink,
			  struct tc_gred_qopt_offload *opt)
{
	switch (opt->command) {
	case TC_GRED_REPLACE:
		return nfp_abm_gred_replace(netdev, alink, opt);
	case TC_GRED_DESTROY:
		nfp_abm_qdisc_destroy(netdev, alink, opt->handle);
		return 0;
	case TC_GRED_STATS:
		return nfp_abm_gred_stats(alink, opt->handle, &opt->stats);
	default:
		return -EOPNOTSUPP;
	}
}