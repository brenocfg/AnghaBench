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
struct TYPE_6__ {scalar_t__ protocol; int /*<<< orphan*/  extack; } ;
struct tc_cls_bpf_offload {scalar_t__ command; struct bpf_prog* prog; TYPE_3__ common; struct bpf_prog* oldprog; int /*<<< orphan*/  exts; int /*<<< orphan*/  exts_integrated; } ;
struct TYPE_4__ {int /*<<< orphan*/  netdev; } ;
struct nfp_net {TYPE_2__* port; struct nfp_bpf_vnic* app_priv; TYPE_1__ dp; } ;
struct nfp_bpf_vnic {struct bpf_prog* tc_prog; } ;
struct bpf_prog {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;
struct TYPE_5__ {int tc_offload_cnt; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_ALL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TC_CLSBPF_OFFLOAD ; 
 int TC_SETUP_CLSBPF ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int nfp_net_bpf_offload (struct nfp_net*,struct bpf_prog*,struct bpf_prog*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_ebpf_capable (struct nfp_net*) ; 
 int /*<<< orphan*/  tc_cls_can_offload_and_chain0 (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ tcf_exts_has_actions (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp_bpf_setup_tc_block_cb(enum tc_setup_type type,
				     void *type_data, void *cb_priv)
{
	struct tc_cls_bpf_offload *cls_bpf = type_data;
	struct nfp_net *nn = cb_priv;
	struct bpf_prog *oldprog;
	struct nfp_bpf_vnic *bv;
	int err;

	if (type != TC_SETUP_CLSBPF) {
		NL_SET_ERR_MSG_MOD(cls_bpf->common.extack,
				   "only offload of BPF classifiers supported");
		return -EOPNOTSUPP;
	}
	if (!tc_cls_can_offload_and_chain0(nn->dp.netdev, &cls_bpf->common))
		return -EOPNOTSUPP;
	if (!nfp_net_ebpf_capable(nn)) {
		NL_SET_ERR_MSG_MOD(cls_bpf->common.extack,
				   "NFP firmware does not support eBPF offload");
		return -EOPNOTSUPP;
	}
	if (cls_bpf->common.protocol != htons(ETH_P_ALL)) {
		NL_SET_ERR_MSG_MOD(cls_bpf->common.extack,
				   "only ETH_P_ALL supported as filter protocol");
		return -EOPNOTSUPP;
	}

	/* Only support TC direct action */
	if (!cls_bpf->exts_integrated ||
	    tcf_exts_has_actions(cls_bpf->exts)) {
		NL_SET_ERR_MSG_MOD(cls_bpf->common.extack,
				   "only direct action with no legacy actions supported");
		return -EOPNOTSUPP;
	}

	if (cls_bpf->command != TC_CLSBPF_OFFLOAD)
		return -EOPNOTSUPP;

	bv = nn->app_priv;
	oldprog = cls_bpf->oldprog;

	/* Don't remove if oldprog doesn't match driver's state */
	if (bv->tc_prog != oldprog) {
		oldprog = NULL;
		if (!cls_bpf->prog)
			return 0;
	}

	err = nfp_net_bpf_offload(nn, cls_bpf->prog, oldprog,
				  cls_bpf->common.extack);
	if (err)
		return err;

	bv->tc_prog = cls_bpf->prog;
	nn->port->tc_offload_cnt = !!bv->tc_prog;
	return 0;
}