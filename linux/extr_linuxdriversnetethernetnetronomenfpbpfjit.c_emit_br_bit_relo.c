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
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int error; int prog_len; int /*<<< orphan*/ * prog; } ;
struct nfp_insn_re_regs {int /*<<< orphan*/  src_lmextn; int /*<<< orphan*/  breg; int /*<<< orphan*/  areg; } ;
typedef  enum nfp_relo_type { ____Placeholder_nfp_relo_type } nfp_relo_type ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OP_RELO_TYPE ; 
 int /*<<< orphan*/  __emit_br_bit (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_imm (int) ; 
 int /*<<< orphan*/  reg_none () ; 
 int swreg_to_restricted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_insn_re_regs*,int) ; 

__attribute__((used)) static void
emit_br_bit_relo(struct nfp_prog *nfp_prog, swreg src, u8 bit, u16 addr,
		 u8 defer, bool set, enum nfp_relo_type relo)
{
	struct nfp_insn_re_regs reg;
	int err;

	/* NOTE: The bit to test is specified as an rotation amount, such that
	 *	 the bit to test will be placed on the MSB of the result when
	 *	 doing a rotate right. For bit X, we need right rotate X + 1.
	 */
	bit += 1;

	err = swreg_to_restricted(reg_none(), src, reg_imm(bit), &reg, false);
	if (err) {
		nfp_prog->error = err;
		return;
	}

	__emit_br_bit(nfp_prog, reg.areg, reg.breg, addr, defer, set,
		      reg.src_lmextn);

	nfp_prog->prog[nfp_prog->prog_len - 1] |=
		FIELD_PREP(OP_RELO_TYPE, relo);
}