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
struct nfp_prog {int /*<<< orphan*/  verifier_meta; int /*<<< orphan*/  bpf; int /*<<< orphan*/  type; int /*<<< orphan*/  insns; } ;
struct nfp_net {int dummy; } ;
struct nfp_app {int /*<<< orphan*/  priv; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; struct bpf_prog* prog; } ;
struct netdev_bpf {TYPE_3__ verifier; } ;
struct bpf_prog {int /*<<< orphan*/  len; int /*<<< orphan*/  insnsi; int /*<<< orphan*/  type; TYPE_2__* aux; } ;
struct TYPE_5__ {TYPE_1__* offload; } ;
struct TYPE_4__ {struct nfp_prog* dev_priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nfp_prog* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_bpf_analyzer_ops ; 
 int /*<<< orphan*/  nfp_prog_first_meta (struct nfp_prog*) ; 
 int /*<<< orphan*/  nfp_prog_free (struct nfp_prog*) ; 
 int nfp_prog_prepare (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_bpf_verifier_prep(struct nfp_app *app, struct nfp_net *nn,
		      struct netdev_bpf *bpf)
{
	struct bpf_prog *prog = bpf->verifier.prog;
	struct nfp_prog *nfp_prog;
	int ret;

	nfp_prog = kzalloc(sizeof(*nfp_prog), GFP_KERNEL);
	if (!nfp_prog)
		return -ENOMEM;
	prog->aux->offload->dev_priv = nfp_prog;

	INIT_LIST_HEAD(&nfp_prog->insns);
	nfp_prog->type = prog->type;
	nfp_prog->bpf = app->priv;

	ret = nfp_prog_prepare(nfp_prog, prog->insnsi, prog->len);
	if (ret)
		goto err_free;

	nfp_prog->verifier_meta = nfp_prog_first_meta(nfp_prog);
	bpf->verifier.ops = &nfp_bpf_analyzer_ops;

	return 0;

err_free:
	nfp_prog_free(nfp_prog);

	return ret;
}