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
struct nfp_app_bpf {int cmsg_cache_cnt; scalar_t__ cmsg_multi_ent; TYPE_1__* app; } ;
struct nfp_app {TYPE_3__* ctrl; struct nfp_app_bpf* priv; } ;
struct TYPE_5__ {scalar_t__ mtu; } ;
struct TYPE_6__ {TYPE_2__ dp; } ;
struct TYPE_4__ {int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 int EINVAL ; 
 int nfp_bpf_ctrl_cmsg_cache_cnt (struct nfp_app_bpf*) ; 
 scalar_t__ nfp_bpf_ctrl_cmsg_min_mtu (struct nfp_app_bpf*) ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int nfp_bpf_start(struct nfp_app *app)
{
	struct nfp_app_bpf *bpf = app->priv;

	if (app->ctrl->dp.mtu < nfp_bpf_ctrl_cmsg_min_mtu(bpf)) {
		nfp_err(bpf->app->cpp,
			"ctrl channel MTU below min required %u < %u\n",
			app->ctrl->dp.mtu, nfp_bpf_ctrl_cmsg_min_mtu(bpf));
		return -EINVAL;
	}

	if (bpf->cmsg_multi_ent)
		bpf->cmsg_cache_cnt = nfp_bpf_ctrl_cmsg_cache_cnt(bpf);
	else
		bpf->cmsg_cache_cnt = 1;

	return 0;
}