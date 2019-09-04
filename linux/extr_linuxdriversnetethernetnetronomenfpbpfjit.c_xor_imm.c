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
 int /*<<< orphan*/  ALU_OP_XOR ; 
 int wrp_alu32_imm (struct nfp_prog*,struct nfp_insn_meta*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xor_imm(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	return wrp_alu32_imm(nfp_prog, meta, ALU_OP_XOR);
}