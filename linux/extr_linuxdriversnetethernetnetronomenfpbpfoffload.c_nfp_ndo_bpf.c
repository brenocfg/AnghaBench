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
struct nfp_net {int dummy; } ;
struct nfp_app {int /*<<< orphan*/  priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  prog; } ;
struct netdev_bpf {int command; int /*<<< orphan*/  offmap; TYPE_1__ offload; } ;

/* Variables and functions */
#define  BPF_OFFLOAD_DESTROY 132 
#define  BPF_OFFLOAD_MAP_ALLOC 131 
#define  BPF_OFFLOAD_MAP_FREE 130 
#define  BPF_OFFLOAD_TRANSLATE 129 
#define  BPF_OFFLOAD_VERIFIER_PREP 128 
 int EINVAL ; 
 int nfp_bpf_destroy (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int nfp_bpf_map_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfp_bpf_map_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfp_bpf_translate (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int nfp_bpf_verifier_prep (struct nfp_app*,struct nfp_net*,struct netdev_bpf*) ; 

int nfp_ndo_bpf(struct nfp_app *app, struct nfp_net *nn, struct netdev_bpf *bpf)
{
	switch (bpf->command) {
	case BPF_OFFLOAD_VERIFIER_PREP:
		return nfp_bpf_verifier_prep(app, nn, bpf);
	case BPF_OFFLOAD_TRANSLATE:
		return nfp_bpf_translate(nn, bpf->offload.prog);
	case BPF_OFFLOAD_DESTROY:
		return nfp_bpf_destroy(nn, bpf->offload.prog);
	case BPF_OFFLOAD_MAP_ALLOC:
		return nfp_bpf_map_alloc(app->priv, bpf->offmap);
	case BPF_OFFLOAD_MAP_FREE:
		return nfp_bpf_map_free(app->priv, bpf->offmap);
	default:
		return -EINVAL;
	}
}