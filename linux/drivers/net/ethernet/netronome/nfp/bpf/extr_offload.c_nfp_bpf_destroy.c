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
struct nfp_prog {int /*<<< orphan*/  bpf; int /*<<< orphan*/  prog; } ;
struct bpf_prog {TYPE_2__* aux; } ;
struct TYPE_4__ {TYPE_1__* offload; } ;
struct TYPE_3__ {struct nfp_prog* dev_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_map_ptrs_forget (int /*<<< orphan*/ ,struct nfp_prog*) ; 
 int /*<<< orphan*/  nfp_prog_free (struct nfp_prog*) ; 

__attribute__((used)) static void nfp_bpf_destroy(struct bpf_prog *prog)
{
	struct nfp_prog *nfp_prog = prog->aux->offload->dev_priv;

	kvfree(nfp_prog->prog);
	nfp_map_ptrs_forget(nfp_prog->bpf, nfp_prog);
	nfp_prog_free(nfp_prog);
}