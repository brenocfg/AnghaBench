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
struct tc_root_qopt_offload {int /*<<< orphan*/  handle; scalar_t__ ingress; } ;
struct nfp_abm_link {TYPE_1__* root_qdisc; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_cnt; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 TYPE_1__* nfp_abm_qdisc_find (struct nfp_abm_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_abm_qdisc_offload_update (struct nfp_abm_link*) ; 

int nfp_abm_setup_root(struct net_device *netdev, struct nfp_abm_link *alink,
		       struct tc_root_qopt_offload *opt)
{
	if (opt->ingress)
		return -EOPNOTSUPP;
	if (alink->root_qdisc)
		alink->root_qdisc->use_cnt--;
	alink->root_qdisc = nfp_abm_qdisc_find(alink, opt->handle);
	if (alink->root_qdisc)
		alink->root_qdisc->use_cnt++;

	nfp_abm_qdisc_offload_update(alink);

	return 0;
}