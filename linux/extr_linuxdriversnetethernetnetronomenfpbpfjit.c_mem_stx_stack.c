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
struct nfp_prog {int dummy; } ;
struct TYPE_2__ {int src_reg; int dst_reg; } ;
struct nfp_insn_meta {TYPE_1__ insn; } ;

/* Variables and functions */
 int mem_op_stack (struct nfp_prog*,struct nfp_insn_meta*,unsigned int,unsigned int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_lmem_store ; 

__attribute__((used)) static int
mem_stx_stack(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta,
	      unsigned int size, unsigned int ptr_off)
{
	return mem_op_stack(nfp_prog, meta, size, ptr_off,
			    meta->insn.src_reg * 2, meta->insn.dst_reg * 2,
			    false, wrp_lmem_store);
}