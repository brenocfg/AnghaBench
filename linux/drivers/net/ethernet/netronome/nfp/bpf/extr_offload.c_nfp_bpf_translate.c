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
typedef  int /*<<< orphan*/  u64 ;
struct nfp_prog {unsigned int __prog_alloc_len; int prog_len; int /*<<< orphan*/  bpf; scalar_t__ prog; } ;
struct nfp_net {int dummy; } ;
struct bpf_prog {TYPE_2__* aux; } ;
struct TYPE_4__ {TYPE_1__* offload; } ;
struct TYPE_3__ {int jited_len; scalar_t__ jited_image; scalar_t__ opt_failed; struct nfp_prog* dev_priv; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFP_NET_CFG_BPF_MAX_LEN ; 
 scalar_t__ kvmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 struct nfp_net* netdev_priv (int /*<<< orphan*/ ) ; 
 int nfp_bpf_jit (struct nfp_prog*) ; 
 int nfp_map_ptrs_record (int /*<<< orphan*/ ,struct nfp_prog*,struct bpf_prog*) ; 
 unsigned int nn_readw (struct nfp_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp_bpf_translate(struct bpf_prog *prog)
{
	struct nfp_net *nn = netdev_priv(prog->aux->offload->netdev);
	struct nfp_prog *nfp_prog = prog->aux->offload->dev_priv;
	unsigned int max_instr;
	int err;

	/* We depend on dead code elimination succeeding */
	if (prog->aux->offload->opt_failed)
		return -EINVAL;

	max_instr = nn_readw(nn, NFP_NET_CFG_BPF_MAX_LEN);
	nfp_prog->__prog_alloc_len = max_instr * sizeof(u64);

	nfp_prog->prog = kvmalloc(nfp_prog->__prog_alloc_len, GFP_KERNEL);
	if (!nfp_prog->prog)
		return -ENOMEM;

	err = nfp_bpf_jit(nfp_prog);
	if (err)
		return err;

	prog->aux->offload->jited_len = nfp_prog->prog_len * sizeof(u64);
	prog->aux->offload->jited_image = nfp_prog->prog;

	return nfp_map_ptrs_record(nfp_prog->bpf, nfp_prog, prog);
}