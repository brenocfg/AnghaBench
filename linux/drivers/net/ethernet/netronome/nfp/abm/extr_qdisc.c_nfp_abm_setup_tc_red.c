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
struct tc_red_qopt_offload {int command; int /*<<< orphan*/  child_handle; int /*<<< orphan*/  handle; int /*<<< orphan*/  stats; } ;
struct nfp_abm_link {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_RED_DESTROY 132 
#define  TC_RED_GRAFT 131 
#define  TC_RED_REPLACE 130 
#define  TC_RED_STATS 129 
#define  TC_RED_XSTATS 128 
 int /*<<< orphan*/  nfp_abm_qdisc_destroy (struct net_device*,struct nfp_abm_link*,int /*<<< orphan*/ ) ; 
 int nfp_abm_qdisc_graft (struct nfp_abm_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfp_abm_red_replace (struct net_device*,struct nfp_abm_link*,struct tc_red_qopt_offload*) ; 
 int nfp_abm_red_stats (struct nfp_abm_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nfp_abm_red_xstats (struct nfp_abm_link*,struct tc_red_qopt_offload*) ; 

int nfp_abm_setup_tc_red(struct net_device *netdev, struct nfp_abm_link *alink,
			 struct tc_red_qopt_offload *opt)
{
	switch (opt->command) {
	case TC_RED_REPLACE:
		return nfp_abm_red_replace(netdev, alink, opt);
	case TC_RED_DESTROY:
		nfp_abm_qdisc_destroy(netdev, alink, opt->handle);
		return 0;
	case TC_RED_STATS:
		return nfp_abm_red_stats(alink, opt->handle, &opt->stats);
	case TC_RED_XSTATS:
		return nfp_abm_red_xstats(alink, opt);
	case TC_RED_GRAFT:
		return nfp_abm_qdisc_graft(alink, opt->handle,
					   opt->child_handle, 0);
	default:
		return -EOPNOTSUPP;
	}
}