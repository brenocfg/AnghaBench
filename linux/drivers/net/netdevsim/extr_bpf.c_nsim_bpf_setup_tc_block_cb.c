#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ protocol; int /*<<< orphan*/  extack; } ;
struct tc_cls_bpf_offload {scalar_t__ command; struct bpf_prog* prog; TYPE_2__ common; struct bpf_prog* oldprog; } ;
struct netdevsim {struct bpf_prog* bpf_offloaded; int /*<<< orphan*/  bpf_tc_non_bound_accept; int /*<<< orphan*/  bpf_tc_accept; int /*<<< orphan*/  netdev; } ;
struct bpf_prog {TYPE_1__* aux; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;
struct TYPE_3__ {int /*<<< orphan*/  offload; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_ALL ; 
 int /*<<< orphan*/  NSIM_EA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TC_CLSBPF_OFFLOAD ; 
 int TC_SETUP_CLSBPF ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int nsim_bpf_offload (struct netdevsim*,struct bpf_prog*,struct bpf_prog*) ; 
 int /*<<< orphan*/  tc_cls_can_offload_and_chain0 (int /*<<< orphan*/ ,TYPE_2__*) ; 

int nsim_bpf_setup_tc_block_cb(enum tc_setup_type type,
			       void *type_data, void *cb_priv)
{
	struct tc_cls_bpf_offload *cls_bpf = type_data;
	struct bpf_prog *prog = cls_bpf->prog;
	struct netdevsim *ns = cb_priv;
	struct bpf_prog *oldprog;

	if (type != TC_SETUP_CLSBPF) {
		NSIM_EA(cls_bpf->common.extack,
			"only offload of BPF classifiers supported");
		return -EOPNOTSUPP;
	}

	if (!tc_cls_can_offload_and_chain0(ns->netdev, &cls_bpf->common))
		return -EOPNOTSUPP;

	if (cls_bpf->common.protocol != htons(ETH_P_ALL)) {
		NSIM_EA(cls_bpf->common.extack,
			"only ETH_P_ALL supported as filter protocol");
		return -EOPNOTSUPP;
	}

	if (!ns->bpf_tc_accept) {
		NSIM_EA(cls_bpf->common.extack,
			"netdevsim configured to reject BPF TC offload");
		return -EOPNOTSUPP;
	}
	/* Note: progs without skip_sw will probably not be dev bound */
	if (prog && !prog->aux->offload && !ns->bpf_tc_non_bound_accept) {
		NSIM_EA(cls_bpf->common.extack,
			"netdevsim configured to reject unbound programs");
		return -EOPNOTSUPP;
	}

	if (cls_bpf->command != TC_CLSBPF_OFFLOAD)
		return -EOPNOTSUPP;

	oldprog = cls_bpf->oldprog;

	/* Don't remove if oldprog doesn't match driver's state */
	if (ns->bpf_offloaded != oldprog) {
		oldprog = NULL;
		if (!cls_bpf->prog)
			return 0;
		if (ns->bpf_offloaded) {
			NSIM_EA(cls_bpf->common.extack,
				"driver and netdev offload states mismatch");
			return -EBUSY;
		}
	}

	return nsim_bpf_offload(ns, cls_bpf->prog, oldprog);
}