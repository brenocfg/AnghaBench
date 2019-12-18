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
struct nfp_prog {int /*<<< orphan*/  stack_frame_depth; TYPE_1__* subprog; } ;
struct nfp_insn_meta {size_t subprog_idx; } ;
struct TYPE_2__ {unsigned int stack_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_subprog_prologue (struct nfp_prog*,struct nfp_insn_meta*) ; 
 int /*<<< orphan*/  round_up (unsigned int,int) ; 

__attribute__((used)) static void
nfp_start_subprog(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	unsigned int depth = nfp_prog->subprog[meta->subprog_idx].stack_depth;

	nfp_prog->stack_frame_depth = round_up(depth, 4);
	nfp_subprog_prologue(nfp_prog, meta);
}