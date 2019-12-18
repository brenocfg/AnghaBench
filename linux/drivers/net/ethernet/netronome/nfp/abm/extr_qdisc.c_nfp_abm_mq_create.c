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
struct tc_mq_qopt_offload {int /*<<< orphan*/  handle; } ;
struct nfp_qdisc {int params_ok; int offloaded; } ;
struct nfp_abm_link {int /*<<< orphan*/  total_queues; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_QDISC_MQ ; 
 int /*<<< orphan*/  TC_H_ROOT ; 
 int /*<<< orphan*/  nfp_abm_qdisc_offload_update (struct nfp_abm_link*) ; 
 int nfp_abm_qdisc_replace (struct net_device*,struct nfp_abm_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_qdisc**) ; 

__attribute__((used)) static int
nfp_abm_mq_create(struct net_device *netdev, struct nfp_abm_link *alink,
		  struct tc_mq_qopt_offload *opt)
{
	struct nfp_qdisc *qdisc;
	int ret;

	ret = nfp_abm_qdisc_replace(netdev, alink, NFP_QDISC_MQ,
				    TC_H_ROOT, opt->handle, alink->total_queues,
				    &qdisc);
	if (ret < 0)
		return ret;

	qdisc->params_ok = true;
	qdisc->offloaded = true;
	nfp_abm_qdisc_offload_update(alink);
	return 0;
}