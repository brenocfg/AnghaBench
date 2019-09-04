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
struct nfp_prog {int /*<<< orphan*/  n_translated; } ;

/* Variables and functions */
 int EINVAL ; 
 int nfp_bpf_optimize (struct nfp_prog*) ; 
 int /*<<< orphan*/  nfp_bpf_prog_trim (struct nfp_prog*) ; 
 int nfp_bpf_replace_map_ptrs (struct nfp_prog*) ; 
 int nfp_translate (struct nfp_prog*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 

int nfp_bpf_jit(struct nfp_prog *nfp_prog)
{
	int ret;

	ret = nfp_bpf_replace_map_ptrs(nfp_prog);
	if (ret)
		return ret;

	ret = nfp_bpf_optimize(nfp_prog);
	if (ret)
		return ret;

	ret = nfp_translate(nfp_prog);
	if (ret) {
		pr_err("Translation failed with error %d (translated: %u)\n",
		       ret, nfp_prog->n_translated);
		return -EINVAL;
	}

	nfp_bpf_prog_trim(nfp_prog);

	return ret;
}