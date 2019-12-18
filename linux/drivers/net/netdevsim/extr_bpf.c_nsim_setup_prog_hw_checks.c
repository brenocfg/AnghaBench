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
struct nsim_bpf_bound_prog {int /*<<< orphan*/  state; } ;
struct netdevsim {int /*<<< orphan*/  netdev; } ;
struct netdev_bpf {int /*<<< orphan*/  extack; TYPE_3__* prog; } ;
struct TYPE_6__ {TYPE_2__* aux; } ;
struct TYPE_5__ {TYPE_1__* offload; } ;
struct TYPE_4__ {struct nsim_bpf_bound_prog* dev_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NSIM_EA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_offload_dev_match (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
nsim_setup_prog_hw_checks(struct netdevsim *ns, struct netdev_bpf *bpf)
{
	struct nsim_bpf_bound_prog *state;

	if (!bpf->prog)
		return 0;

	if (!bpf->prog->aux->offload) {
		NSIM_EA(bpf->extack, "xdpoffload of non-bound program");
		return -EINVAL;
	}
	if (!bpf_offload_dev_match(bpf->prog, ns->netdev)) {
		NSIM_EA(bpf->extack, "program bound to different dev");
		return -EINVAL;
	}

	state = bpf->prog->aux->offload->dev_priv;
	if (WARN_ON(strcmp(state->state, "xlated"))) {
		NSIM_EA(bpf->extack, "offloading program in bad state");
		return -EINVAL;
	}
	return 0;
}