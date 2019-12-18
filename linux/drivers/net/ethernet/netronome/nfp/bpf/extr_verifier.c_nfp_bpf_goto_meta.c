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
struct nfp_prog {unsigned int n_insns; } ;
struct nfp_insn_meta {unsigned int n; } ;

/* Variables and functions */
 unsigned int min (unsigned int,unsigned int) ; 
 struct nfp_insn_meta* nfp_meta_next (struct nfp_insn_meta*) ; 
 struct nfp_insn_meta* nfp_meta_prev (struct nfp_insn_meta*) ; 
 struct nfp_insn_meta* nfp_prog_first_meta (struct nfp_prog*) ; 
 struct nfp_insn_meta* nfp_prog_last_meta (struct nfp_prog*) ; 

struct nfp_insn_meta *
nfp_bpf_goto_meta(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta,
		  unsigned int insn_idx)
{
	unsigned int forward, backward, i;

	backward = meta->n - insn_idx;
	forward = insn_idx - meta->n;

	if (min(forward, backward) > nfp_prog->n_insns - insn_idx - 1) {
		backward = nfp_prog->n_insns - insn_idx - 1;
		meta = nfp_prog_last_meta(nfp_prog);
	}
	if (min(forward, backward) > insn_idx && backward > insn_idx) {
		forward = insn_idx;
		meta = nfp_prog_first_meta(nfp_prog);
	}

	if (forward < backward)
		for (i = 0; i < forward; i++)
			meta = nfp_meta_next(meta);
	else
		for (i = 0; i < backward; i++)
			meta = nfp_meta_prev(meta);

	return meta;
}