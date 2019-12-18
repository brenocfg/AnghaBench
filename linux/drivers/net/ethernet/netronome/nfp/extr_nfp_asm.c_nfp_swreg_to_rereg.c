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
typedef  int u16 ;
typedef  int /*<<< orphan*/  swreg ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NN_LM_MOD_NONE ; 
#define  NN_REG_GPR_A 135 
#define  NN_REG_GPR_B 134 
#define  NN_REG_GPR_BOTH 133 
#define  NN_REG_IMM 132 
#define  NN_REG_LMEM 131 
#define  NN_REG_NNR 130 
#define  NN_REG_NONE 129 
#define  NN_REG_XFER 128 
 int REG_NONE ; 
 int RE_REG_IMM_encode (int) ; 
 int RE_REG_LM ; 
 int /*<<< orphan*/  RE_REG_LM_IDX ; 
 int RE_REG_LM_IDX_MAX ; 
 int RE_REG_NO_DST ; 
 int RE_REG_XFR ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int swreg_lm_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swreg_lm_mode (int /*<<< orphan*/ ) ; 
 int swreg_type (int /*<<< orphan*/ ) ; 
 int swreg_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 nfp_swreg_to_rereg(swreg reg, bool is_dst, bool has_imm8, bool *i8)
{
	u16 val = swreg_value(reg);
	bool lm_id;

	switch (swreg_type(reg)) {
	case NN_REG_GPR_A:
	case NN_REG_GPR_B:
	case NN_REG_GPR_BOTH:
		return val;
	case NN_REG_XFER:
		return RE_REG_XFR | val;
	case NN_REG_LMEM:
		lm_id = swreg_lm_idx(reg);

		if (swreg_lm_mode(reg) != NN_LM_MOD_NONE) {
			pr_err("bad LM mode for restricted operands %d\n",
			       swreg_lm_mode(reg));
			return 0;
		}

		if (val & ~RE_REG_LM_IDX_MAX) {
			pr_err("LM offset too large\n");
			return 0;
		}

		return RE_REG_LM | FIELD_PREP(RE_REG_LM_IDX, lm_id) | val;
	case NN_REG_IMM:
		if (val & ~(0x7f | has_imm8 << 7)) {
			pr_err("immediate too large\n");
			return 0;
		}
		*i8 = val & 0x80;
		return RE_REG_IMM_encode(val & 0x7f);
	case NN_REG_NONE:
		return is_dst ? RE_REG_NO_DST : REG_NONE;
	case NN_REG_NNR:
		pr_err("NNRs used with restricted encoding\n");
		return 0;
	}

	pr_err("unrecognized reg encoding\n");
	return 0;
}