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
struct nfp_prog {scalar_t__ type; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct nfp_insn_meta {TYPE_1__ ptr; } ;

/* Variables and functions */
 scalar_t__ BPF_PROG_TYPE_XDP ; 
 scalar_t__ PTR_TO_CTX ; 
 int mem_stx (struct nfp_prog*,struct nfp_insn_meta*,int) ; 
 int mem_stx_xdp (struct nfp_prog*,struct nfp_insn_meta*) ; 

__attribute__((used)) static int mem_stx4(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	if (meta->ptr.type == PTR_TO_CTX)
		if (nfp_prog->type == BPF_PROG_TYPE_XDP)
			return mem_stx_xdp(nfp_prog, meta);
	return mem_stx(nfp_prog, meta, 4);
}