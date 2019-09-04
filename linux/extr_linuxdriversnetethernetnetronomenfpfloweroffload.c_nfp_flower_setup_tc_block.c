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
struct tc_block_offload {scalar_t__ binder_type; int command; int /*<<< orphan*/  block; int /*<<< orphan*/  extack; } ;
struct nfp_repr {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ TCF_BLOCK_BINDER_TYPE_CLSACT_INGRESS ; 
#define  TC_BLOCK_BIND 129 
#define  TC_BLOCK_UNBIND 128 
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nfp_flower_setup_tc_block_cb ; 
 int tcf_block_cb_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_repr*,struct nfp_repr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_block_cb_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_repr*) ; 

__attribute__((used)) static int nfp_flower_setup_tc_block(struct net_device *netdev,
				     struct tc_block_offload *f)
{
	struct nfp_repr *repr = netdev_priv(netdev);

	if (f->binder_type != TCF_BLOCK_BINDER_TYPE_CLSACT_INGRESS)
		return -EOPNOTSUPP;

	switch (f->command) {
	case TC_BLOCK_BIND:
		return tcf_block_cb_register(f->block,
					     nfp_flower_setup_tc_block_cb,
					     repr, repr, f->extack);
	case TC_BLOCK_UNBIND:
		tcf_block_cb_unregister(f->block,
					nfp_flower_setup_tc_block_cb,
					repr);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}