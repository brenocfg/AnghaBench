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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int error; } ;
struct nfp_insn_ur_regs {int /*<<< orphan*/  src_lmextn; int /*<<< orphan*/  dst_lmextn; int /*<<< orphan*/  wr_both; int /*<<< orphan*/  swap; int /*<<< orphan*/  breg; int /*<<< orphan*/  dst_ab; int /*<<< orphan*/  areg; int /*<<< orphan*/  dst; } ;
typedef  enum mul_type { ____Placeholder_mul_type } mul_type ;
typedef  enum mul_step { ____Placeholder_mul_step } mul_step ;

/* Variables and functions */
 int EINVAL ; 
 int MUL_LAST ; 
 int MUL_LAST_2 ; 
 int MUL_STEP_NONE ; 
 int MUL_TYPE_START ; 
 int /*<<< orphan*/  __emit_mul (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_none () ; 
 int swreg_to_unrestricted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_insn_ur_regs*) ; 

__attribute__((used)) static void
emit_mul(struct nfp_prog *nfp_prog, swreg lreg, enum mul_type type,
	 enum mul_step step, swreg rreg)
{
	struct nfp_insn_ur_regs reg;
	u16 areg;
	int err;

	if (type == MUL_TYPE_START && step != MUL_STEP_NONE) {
		nfp_prog->error = -EINVAL;
		return;
	}

	if (step == MUL_LAST || step == MUL_LAST_2) {
		/* When type is step and step Number is LAST or LAST2, left
		 * source is used as destination.
		 */
		err = swreg_to_unrestricted(lreg, reg_none(), rreg, &reg);
		areg = reg.dst;
	} else {
		err = swreg_to_unrestricted(reg_none(), lreg, rreg, &reg);
		areg = reg.areg;
	}

	if (err) {
		nfp_prog->error = err;
		return;
	}

	__emit_mul(nfp_prog, reg.dst_ab, areg, type, step, reg.breg, reg.swap,
		   reg.wr_both, reg.dst_lmextn, reg.src_lmextn);
}