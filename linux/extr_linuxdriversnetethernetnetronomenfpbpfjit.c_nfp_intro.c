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

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_AND ; 
 int /*<<< orphan*/  GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plen_reg (struct nfp_prog*) ; 
 int /*<<< orphan*/  pv_len (struct nfp_prog*) ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_intro(struct nfp_prog *nfp_prog)
{
	wrp_immed(nfp_prog, plen_reg(nfp_prog), GENMASK(13, 0));
	emit_alu(nfp_prog, plen_reg(nfp_prog),
		 plen_reg(nfp_prog), ALU_OP_AND, pv_len(nfp_prog));
}