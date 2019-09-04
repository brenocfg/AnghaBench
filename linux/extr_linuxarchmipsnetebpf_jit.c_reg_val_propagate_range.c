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
typedef  int u64 ;
typedef  int u32 ;
struct jit_ctx {int* reg_val_types; struct bpf_prog* skf; } ;
struct bpf_prog {int len; struct bpf_insn* insnsi; } ;
struct bpf_insn {int dst_reg; int imm; int off; int /*<<< orphan*/  code; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
#define  BPF_ADD 163 
#define  BPF_ALU 162 
#define  BPF_ALU64 161 
#define  BPF_AND 160 
#define  BPF_B 159 
#define  BPF_CALL 158 
 int BPF_CLASS (int /*<<< orphan*/ ) ; 
#define  BPF_DIV 157 
#define  BPF_DW 156 
#define  BPF_END 155 
#define  BPF_EXIT 154 
#define  BPF_H 153 
 int /*<<< orphan*/  BPF_IMM ; 
#define  BPF_JA 152 
#define  BPF_JEQ 151 
#define  BPF_JGE 150 
#define  BPF_JGT 149 
#define  BPF_JLE 148 
#define  BPF_JLT 147 
#define  BPF_JMP 146 
#define  BPF_JNE 145 
#define  BPF_JSET 144 
#define  BPF_JSGE 143 
#define  BPF_JSGT 142 
#define  BPF_JSLE 141 
#define  BPF_JSLT 140 
#define  BPF_LD 139 
#define  BPF_LDX 138 
#define  BPF_LSH 137 
#define  BPF_MOD 136 
 int /*<<< orphan*/  BPF_MODE (int /*<<< orphan*/ ) ; 
#define  BPF_MOV 135 
#define  BPF_MUL 134 
#define  BPF_NEG 133 
 int /*<<< orphan*/  BPF_OP (int /*<<< orphan*/ ) ; 
#define  BPF_OR 132 
 int BPF_REG_0 ; 
 int BPF_REG_5 ; 
#define  BPF_RSH 131 
 int /*<<< orphan*/  BPF_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_SRC (int /*<<< orphan*/ ) ; 
#define  BPF_SUB 130 
#define  BPF_W 129 
#define  BPF_XOR 128 
 int /*<<< orphan*/  REG_32BIT ; 
 int /*<<< orphan*/  REG_32BIT_POS ; 
 int /*<<< orphan*/  REG_64BIT ; 
 int /*<<< orphan*/  REG_64BIT_32BIT ; 
 int RVT_BRANCH_TAKEN ; 
 int RVT_DONE ; 
 int RVT_FALL_THROUGH ; 
 int RVT_VISITED_MASK ; 
 int /*<<< orphan*/  S32_MAX ; 
 int /*<<< orphan*/  S32_MIN ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  set_reg_val_type (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reg_val_propagate_range(struct jit_ctx *ctx, u64 initial_rvt,
				   int start_idx, bool follow_taken)
{
	const struct bpf_prog *prog = ctx->skf;
	const struct bpf_insn *insn;
	u64 exit_rvt = initial_rvt;
	u64 *rvt = ctx->reg_val_types;
	int idx;
	int reg;

	for (idx = start_idx; idx < prog->len; idx++) {
		rvt[idx] = (rvt[idx] & RVT_VISITED_MASK) | exit_rvt;
		insn = prog->insnsi + idx;
		switch (BPF_CLASS(insn->code)) {
		case BPF_ALU:
			switch (BPF_OP(insn->code)) {
			case BPF_ADD:
			case BPF_SUB:
			case BPF_MUL:
			case BPF_DIV:
			case BPF_OR:
			case BPF_AND:
			case BPF_LSH:
			case BPF_RSH:
			case BPF_NEG:
			case BPF_MOD:
			case BPF_XOR:
				set_reg_val_type(&exit_rvt, insn->dst_reg, REG_32BIT);
				break;
			case BPF_MOV:
				if (BPF_SRC(insn->code)) {
					set_reg_val_type(&exit_rvt, insn->dst_reg, REG_32BIT);
				} else {
					/* IMM to REG move*/
					if (insn->imm >= 0)
						set_reg_val_type(&exit_rvt, insn->dst_reg, REG_32BIT_POS);
					else
						set_reg_val_type(&exit_rvt, insn->dst_reg, REG_32BIT);
				}
				break;
			case BPF_END:
				if (insn->imm == 64)
					set_reg_val_type(&exit_rvt, insn->dst_reg, REG_64BIT);
				else if (insn->imm == 32)
					set_reg_val_type(&exit_rvt, insn->dst_reg, REG_32BIT);
				else /* insn->imm == 16 */
					set_reg_val_type(&exit_rvt, insn->dst_reg, REG_32BIT_POS);
				break;
			}
			rvt[idx] |= RVT_DONE;
			break;
		case BPF_ALU64:
			switch (BPF_OP(insn->code)) {
			case BPF_MOV:
				if (BPF_SRC(insn->code)) {
					/* REG to REG move*/
					set_reg_val_type(&exit_rvt, insn->dst_reg, REG_64BIT);
				} else {
					/* IMM to REG move*/
					if (insn->imm >= 0)
						set_reg_val_type(&exit_rvt, insn->dst_reg, REG_32BIT_POS);
					else
						set_reg_val_type(&exit_rvt, insn->dst_reg, REG_64BIT_32BIT);
				}
				break;
			default:
				set_reg_val_type(&exit_rvt, insn->dst_reg, REG_64BIT);
			}
			rvt[idx] |= RVT_DONE;
			break;
		case BPF_LD:
			switch (BPF_SIZE(insn->code)) {
			case BPF_DW:
				if (BPF_MODE(insn->code) == BPF_IMM) {
					s64 val;

					val = (s64)((u32)insn->imm | ((u64)(insn + 1)->imm << 32));
					if (val > 0 && val <= S32_MAX)
						set_reg_val_type(&exit_rvt, insn->dst_reg, REG_32BIT_POS);
					else if (val >= S32_MIN && val <= S32_MAX)
						set_reg_val_type(&exit_rvt, insn->dst_reg, REG_64BIT_32BIT);
					else
						set_reg_val_type(&exit_rvt, insn->dst_reg, REG_64BIT);
					rvt[idx] |= RVT_DONE;
					idx++;
				} else {
					set_reg_val_type(&exit_rvt, insn->dst_reg, REG_64BIT);
				}
				break;
			case BPF_B:
			case BPF_H:
				set_reg_val_type(&exit_rvt, insn->dst_reg, REG_32BIT_POS);
				break;
			case BPF_W:
				if (BPF_MODE(insn->code) == BPF_IMM)
					set_reg_val_type(&exit_rvt, insn->dst_reg,
							 insn->imm >= 0 ? REG_32BIT_POS : REG_32BIT);
				else
					set_reg_val_type(&exit_rvt, insn->dst_reg, REG_32BIT);
				break;
			}
			rvt[idx] |= RVT_DONE;
			break;
		case BPF_LDX:
			switch (BPF_SIZE(insn->code)) {
			case BPF_DW:
				set_reg_val_type(&exit_rvt, insn->dst_reg, REG_64BIT);
				break;
			case BPF_B:
			case BPF_H:
				set_reg_val_type(&exit_rvt, insn->dst_reg, REG_32BIT_POS);
				break;
			case BPF_W:
				set_reg_val_type(&exit_rvt, insn->dst_reg, REG_32BIT);
				break;
			}
			rvt[idx] |= RVT_DONE;
			break;
		case BPF_JMP:
			switch (BPF_OP(insn->code)) {
			case BPF_EXIT:
				rvt[idx] = RVT_DONE | exit_rvt;
				rvt[prog->len] = exit_rvt;
				return idx;
			case BPF_JA:
				rvt[idx] |= RVT_DONE;
				idx += insn->off;
				break;
			case BPF_JEQ:
			case BPF_JGT:
			case BPF_JGE:
			case BPF_JLT:
			case BPF_JLE:
			case BPF_JSET:
			case BPF_JNE:
			case BPF_JSGT:
			case BPF_JSGE:
			case BPF_JSLT:
			case BPF_JSLE:
				if (follow_taken) {
					rvt[idx] |= RVT_BRANCH_TAKEN;
					idx += insn->off;
					follow_taken = false;
				} else {
					rvt[idx] |= RVT_FALL_THROUGH;
				}
				break;
			case BPF_CALL:
				set_reg_val_type(&exit_rvt, BPF_REG_0, REG_64BIT);
				/* Upon call return, argument registers are clobbered. */
				for (reg = BPF_REG_0; reg <= BPF_REG_5; reg++)
					set_reg_val_type(&exit_rvt, reg, REG_64BIT);

				rvt[idx] |= RVT_DONE;
				break;
			default:
				WARN(1, "Unhandled BPF_JMP case.\n");
				rvt[idx] |= RVT_DONE;
				break;
			}
			break;
		default:
			rvt[idx] |= RVT_DONE;
			break;
		}
	}
	return idx;
}