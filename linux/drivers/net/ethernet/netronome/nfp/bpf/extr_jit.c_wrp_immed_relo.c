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
typedef  int u32 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int prog_len; int /*<<< orphan*/ * prog; int /*<<< orphan*/  error; } ;
typedef  enum nfp_relo_type { ____Placeholder_nfp_relo_type } nfp_relo_type ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IMMED_SHIFT_0B ; 
 int /*<<< orphan*/  IMMED_WIDTH_ALL ; 
 int /*<<< orphan*/  OP_RELO_TYPE ; 
 int /*<<< orphan*/  emit_immed (struct nfp_prog*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void
wrp_immed_relo(struct nfp_prog *nfp_prog, swreg dst, u32 imm,
	       enum nfp_relo_type relo)
{
	if (imm > 0xffff) {
		pr_err("relocation of a large immediate!\n");
		nfp_prog->error = -EFAULT;
		return;
	}
	emit_immed(nfp_prog, dst, imm, IMMED_WIDTH_ALL, false, IMMED_SHIFT_0B);

	nfp_prog->prog[nfp_prog->prog_len - 1] |=
		FIELD_PREP(OP_RELO_TYPE, relo);
}