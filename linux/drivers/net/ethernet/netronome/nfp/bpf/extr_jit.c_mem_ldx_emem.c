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
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
struct TYPE_2__ {int src_reg; int dst_reg; int /*<<< orphan*/  off; } ;
struct nfp_insn_meta {TYPE_1__ insn; } ;

/* Variables and functions */
 int data_ld_host_order_addr40 (struct nfp_prog*,struct nfp_insn_meta*,int,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  imm_b (struct nfp_prog*) ; 
 int /*<<< orphan*/  re_load_imm_any (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mem_ldx_emem(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta,
	     unsigned int size)
{
	swreg tmp_reg;

	tmp_reg = re_load_imm_any(nfp_prog, meta->insn.off, imm_b(nfp_prog));

	return data_ld_host_order_addr40(nfp_prog, meta, meta->insn.src_reg * 2,
					 tmp_reg, meta->insn.dst_reg * 2, size);
}