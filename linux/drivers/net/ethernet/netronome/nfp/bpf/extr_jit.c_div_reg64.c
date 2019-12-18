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
struct TYPE_2__ {int dst_reg; } ;
struct nfp_insn_meta {int /*<<< orphan*/  umin_src; TYPE_1__ insn; } ;

/* Variables and functions */
 int wrp_div_imm (struct nfp_prog*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int div_reg64(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	/* NOTE: verifier hook has rejected cases for which verifier doesn't
	 * know whether the source operand is constant or not.
	 */
	return wrp_div_imm(nfp_prog, meta->insn.dst_reg * 2, meta->umin_src);
}