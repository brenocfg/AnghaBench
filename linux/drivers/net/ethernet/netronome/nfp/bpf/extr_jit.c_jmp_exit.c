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
struct nfp_prog {int dummy; } ;
struct nfp_insn_meta {int dummy; } ;

/* Variables and functions */
 int goto_out (struct nfp_prog*,struct nfp_insn_meta*) ; 
 scalar_t__ nfp_is_main_function (struct nfp_insn_meta*) ; 
 int nfp_subprog_epilogue (struct nfp_prog*,struct nfp_insn_meta*) ; 

__attribute__((used)) static int jmp_exit(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	if (nfp_is_main_function(meta))
		return goto_out(nfp_prog, meta);
	else
		return nfp_subprog_epilogue(nfp_prog, meta);
}