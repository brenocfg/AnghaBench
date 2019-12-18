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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct nfp_prog {int prog_len; int /*<<< orphan*/ * prog; int /*<<< orphan*/  error; } ;
typedef  enum nfp_relo_type { ____Placeholder_nfp_relo_type } nfp_relo_type ;
typedef  enum br_mask { ____Placeholder_br_mask } br_mask ;

/* Variables and functions */
 int /*<<< orphan*/  BR_CSS_NONE ; 
 int /*<<< orphan*/  BR_EV_PIP_COND ; 
 int /*<<< orphan*/  BR_EV_PIP_UNCOND ; 
 int BR_UNC ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OP_RELO_TYPE ; 
 int /*<<< orphan*/  __emit_br (struct nfp_prog*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static void
emit_br_relo(struct nfp_prog *nfp_prog, enum br_mask mask, u16 addr, u8 defer,
	     enum nfp_relo_type relo)
{
	if (mask == BR_UNC && defer > 2) {
		pr_err("BUG: branch defer out of bounds %d\n", defer);
		nfp_prog->error = -EFAULT;
		return;
	}

	__emit_br(nfp_prog, mask,
		  mask != BR_UNC ? BR_EV_PIP_COND : BR_EV_PIP_UNCOND,
		  BR_CSS_NONE, addr, defer);

	nfp_prog->prog[nfp_prog->prog_len - 1] |=
		FIELD_PREP(OP_RELO_TYPE, relo);
}