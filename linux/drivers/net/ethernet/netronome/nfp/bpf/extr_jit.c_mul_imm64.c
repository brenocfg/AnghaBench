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
 int wrp_mul (struct nfp_prog*,struct nfp_insn_meta*,int,int) ; 

__attribute__((used)) static int mul_imm64(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	return wrp_mul(nfp_prog, meta, true, false);
}