#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int opcode; int const rt; size_t rs; int simmediate; } ;
struct TYPE_9__ {int target; } ;
struct TYPE_8__ {int const func; size_t rd; size_t rs; } ;
union mips_instruction {TYPE_5__ i_format; TYPE_2__ j_format; TYPE_1__ r_format; } ;
struct pt_regs {long cp0_epc; long* regs; } ;
struct TYPE_10__ {unsigned int fcr31; int /*<<< orphan*/ * fpr; } ;
struct TYPE_11__ {TYPE_3__ fpu; } ;
struct TYPE_13__ {int /*<<< orphan*/  comm; TYPE_4__ thread; } ;

/* Variables and functions */
 int BRANCH_LIKELY_TAKEN ; 
 int /*<<< orphan*/  CP1_STATUS ; 
 int EFAULT ; 
 int /*<<< orphan*/  NO_R6EMU ; 
 int /*<<< orphan*/  SIGILL ; 
#define  balc6_op 158 
 size_t bc1eqz_op ; 
 size_t bc1nez_op ; 
#define  bc6_op 157 
#define  bcond_op 156 
#define  beq_op 155 
#define  beql_op 154 
#define  bgez_op 153 
#define  bgezal_op 152 
#define  bgezall_op 151 
#define  bgezl_op 150 
#define  bgtz_op 149 
#define  bgtzl_op 148 
#define  blez_op 147 
#define  blezl_op 146 
#define  bltz_op 145 
#define  bltzal_op 144 
#define  bltzall_op 143 
#define  bltzl_op 142 
#define  bne_op 141 
#define  bnel_op 140 
#define  bposge32_op 139 
#define  cop1_op 138 
 int /*<<< orphan*/  cpu_has_dsp ; 
 int /*<<< orphan*/  cpu_has_mips_r6 ; 
 TYPE_6__* current ; 
 int /*<<< orphan*/  force_sig (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int get_fpr32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int init_fpu () ; 
 int /*<<< orphan*/  is_fpu_owner () ; 
#define  j_op 137 
#define  jal_op 136 
#define  jalr_op 135 
#define  jalx_op 134 
#define  jr_op 133 
 int /*<<< orphan*/  lose_fpu (int) ; 
 int /*<<< orphan*/  own_fpu (int) ; 
#define  pop10_op 132 
#define  pop30_op 131 
#define  pop66_op 130 
#define  pop76_op 129 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 unsigned int rddsp (int) ; 
 unsigned int read_32bit_cp1_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_isa16_mode (long) ; 
 int /*<<< orphan*/  set_used_math () ; 
#define  spec_op 128 
 int /*<<< orphan*/  used_math () ; 

int __compute_return_epc_for_insn(struct pt_regs *regs,
				   union mips_instruction insn)
{
	unsigned int bit, fcr31, dspcontrol, reg;
	long epc = regs->cp0_epc;
	int ret = 0;

	switch (insn.i_format.opcode) {
	/*
	 * jr and jalr are in r_format format.
	 */
	case spec_op:
		switch (insn.r_format.func) {
		case jalr_op:
			regs->regs[insn.r_format.rd] = epc + 8;
			/* Fall through */
		case jr_op:
			if (NO_R6EMU && insn.r_format.func == jr_op)
				goto sigill_r2r6;
			regs->cp0_epc = regs->regs[insn.r_format.rs];
			break;
		}
		break;

	/*
	 * This group contains:
	 * bltz_op, bgez_op, bltzl_op, bgezl_op,
	 * bltzal_op, bgezal_op, bltzall_op, bgezall_op.
	 */
	case bcond_op:
		switch (insn.i_format.rt) {
		case bltzl_op:
			if (NO_R6EMU)
				goto sigill_r2r6;
		case bltz_op:
			if ((long)regs->regs[insn.i_format.rs] < 0) {
				epc = epc + 4 + (insn.i_format.simmediate << 2);
				if (insn.i_format.rt == bltzl_op)
					ret = BRANCH_LIKELY_TAKEN;
			} else
				epc += 8;
			regs->cp0_epc = epc;
			break;

		case bgezl_op:
			if (NO_R6EMU)
				goto sigill_r2r6;
		case bgez_op:
			if ((long)regs->regs[insn.i_format.rs] >= 0) {
				epc = epc + 4 + (insn.i_format.simmediate << 2);
				if (insn.i_format.rt == bgezl_op)
					ret = BRANCH_LIKELY_TAKEN;
			} else
				epc += 8;
			regs->cp0_epc = epc;
			break;

		case bltzal_op:
		case bltzall_op:
			if (NO_R6EMU && (insn.i_format.rs ||
			    insn.i_format.rt == bltzall_op))
				goto sigill_r2r6;
			regs->regs[31] = epc + 8;
			/*
			 * OK we are here either because we hit a NAL
			 * instruction or because we are emulating an
			 * old bltzal{,l} one. Let's figure out what the
			 * case really is.
			 */
			if (!insn.i_format.rs) {
				/*
				 * NAL or BLTZAL with rs == 0
				 * Doesn't matter if we are R6 or not. The
				 * result is the same
				 */
				regs->cp0_epc += 4 +
					(insn.i_format.simmediate << 2);
				break;
			}
			/* Now do the real thing for non-R6 BLTZAL{,L} */
			if ((long)regs->regs[insn.i_format.rs] < 0) {
				epc = epc + 4 + (insn.i_format.simmediate << 2);
				if (insn.i_format.rt == bltzall_op)
					ret = BRANCH_LIKELY_TAKEN;
			} else
				epc += 8;
			regs->cp0_epc = epc;
			break;

		case bgezal_op:
		case bgezall_op:
			if (NO_R6EMU && (insn.i_format.rs ||
			    insn.i_format.rt == bgezall_op))
				goto sigill_r2r6;
			regs->regs[31] = epc + 8;
			/*
			 * OK we are here either because we hit a BAL
			 * instruction or because we are emulating an
			 * old bgezal{,l} one. Let's figure out what the
			 * case really is.
			 */
			if (!insn.i_format.rs) {
				/*
				 * BAL or BGEZAL with rs == 0
				 * Doesn't matter if we are R6 or not. The
				 * result is the same
				 */
				regs->cp0_epc += 4 +
					(insn.i_format.simmediate << 2);
				break;
			}
			/* Now do the real thing for non-R6 BGEZAL{,L} */
			if ((long)regs->regs[insn.i_format.rs] >= 0) {
				epc = epc + 4 + (insn.i_format.simmediate << 2);
				if (insn.i_format.rt == bgezall_op)
					ret = BRANCH_LIKELY_TAKEN;
			} else
				epc += 8;
			regs->cp0_epc = epc;
			break;

		case bposge32_op:
			if (!cpu_has_dsp)
				goto sigill_dsp;

			dspcontrol = rddsp(0x01);

			if (dspcontrol >= 32) {
				epc = epc + 4 + (insn.i_format.simmediate << 2);
			} else
				epc += 8;
			regs->cp0_epc = epc;
			break;
		}
		break;

	/*
	 * These are unconditional and in j_format.
	 */
	case jalx_op:
	case jal_op:
		regs->regs[31] = regs->cp0_epc + 8;
	case j_op:
		epc += 4;
		epc >>= 28;
		epc <<= 28;
		epc |= (insn.j_format.target << 2);
		regs->cp0_epc = epc;
		if (insn.i_format.opcode == jalx_op)
			set_isa16_mode(regs->cp0_epc);
		break;

	/*
	 * These are conditional and in i_format.
	 */
	case beql_op:
		if (NO_R6EMU)
			goto sigill_r2r6;
	case beq_op:
		if (regs->regs[insn.i_format.rs] ==
		    regs->regs[insn.i_format.rt]) {
			epc = epc + 4 + (insn.i_format.simmediate << 2);
			if (insn.i_format.opcode == beql_op)
				ret = BRANCH_LIKELY_TAKEN;
		} else
			epc += 8;
		regs->cp0_epc = epc;
		break;

	case bnel_op:
		if (NO_R6EMU)
			goto sigill_r2r6;
	case bne_op:
		if (regs->regs[insn.i_format.rs] !=
		    regs->regs[insn.i_format.rt]) {
			epc = epc + 4 + (insn.i_format.simmediate << 2);
			if (insn.i_format.opcode == bnel_op)
				ret = BRANCH_LIKELY_TAKEN;
		} else
			epc += 8;
		regs->cp0_epc = epc;
		break;

	case blezl_op: /* not really i_format */
		if (!insn.i_format.rt && NO_R6EMU)
			goto sigill_r2r6;
	case blez_op:
		/*
		 * Compact branches for R6 for the
		 * blez and blezl opcodes.
		 * BLEZ  | rs = 0 | rt != 0  == BLEZALC
		 * BLEZ  | rs = rt != 0      == BGEZALC
		 * BLEZ  | rs != 0 | rt != 0 == BGEUC
		 * BLEZL | rs = 0 | rt != 0  == BLEZC
		 * BLEZL | rs = rt != 0      == BGEZC
		 * BLEZL | rs != 0 | rt != 0 == BGEC
		 *
		 * For real BLEZ{,L}, rt is always 0.
		 */

		if (cpu_has_mips_r6 && insn.i_format.rt) {
			if ((insn.i_format.opcode == blez_op) &&
			    ((!insn.i_format.rs && insn.i_format.rt) ||
			     (insn.i_format.rs == insn.i_format.rt)))
				regs->regs[31] = epc + 4;
			regs->cp0_epc += 8;
			break;
		}
		/* rt field assumed to be zero */
		if ((long)regs->regs[insn.i_format.rs] <= 0) {
			epc = epc + 4 + (insn.i_format.simmediate << 2);
			if (insn.i_format.opcode == blezl_op)
				ret = BRANCH_LIKELY_TAKEN;
		} else
			epc += 8;
		regs->cp0_epc = epc;
		break;

	case bgtzl_op:
		if (!insn.i_format.rt && NO_R6EMU)
			goto sigill_r2r6;
	case bgtz_op:
		/*
		 * Compact branches for R6 for the
		 * bgtz and bgtzl opcodes.
		 * BGTZ  | rs = 0 | rt != 0  == BGTZALC
		 * BGTZ  | rs = rt != 0      == BLTZALC
		 * BGTZ  | rs != 0 | rt != 0 == BLTUC
		 * BGTZL | rs = 0 | rt != 0  == BGTZC
		 * BGTZL | rs = rt != 0      == BLTZC
		 * BGTZL | rs != 0 | rt != 0 == BLTC
		 *
		 * *ZALC varint for BGTZ &&& rt != 0
		 * For real GTZ{,L}, rt is always 0.
		 */
		if (cpu_has_mips_r6 && insn.i_format.rt) {
			if ((insn.i_format.opcode == blez_op) &&
			    ((!insn.i_format.rs && insn.i_format.rt) ||
			    (insn.i_format.rs == insn.i_format.rt)))
				regs->regs[31] = epc + 4;
			regs->cp0_epc += 8;
			break;
		}

		/* rt field assumed to be zero */
		if ((long)regs->regs[insn.i_format.rs] > 0) {
			epc = epc + 4 + (insn.i_format.simmediate << 2);
			if (insn.i_format.opcode == bgtzl_op)
				ret = BRANCH_LIKELY_TAKEN;
		} else
			epc += 8;
		regs->cp0_epc = epc;
		break;

	/*
	 * And now the FPA/cp1 branch instructions.
	 */
	case cop1_op:
		if (cpu_has_mips_r6 &&
		    ((insn.i_format.rs == bc1eqz_op) ||
		     (insn.i_format.rs == bc1nez_op))) {
			if (!used_math()) { /* First time FPU user */
				ret = init_fpu();
				if (ret && NO_R6EMU) {
					ret = -ret;
					break;
				}
				ret = 0;
				set_used_math();
			}
			lose_fpu(1);    /* Save FPU state for the emulator. */
			reg = insn.i_format.rt;
			bit = get_fpr32(&current->thread.fpu.fpr[reg], 0) & 0x1;
			if (insn.i_format.rs == bc1eqz_op)
				bit = !bit;
			own_fpu(1);
			if (bit)
				epc = epc + 4 +
					(insn.i_format.simmediate << 2);
			else
				epc += 8;
			regs->cp0_epc = epc;

			break;
		} else {

			preempt_disable();
			if (is_fpu_owner())
			        fcr31 = read_32bit_cp1_register(CP1_STATUS);
			else
				fcr31 = current->thread.fpu.fcr31;
			preempt_enable();

			bit = (insn.i_format.rt >> 2);
			bit += (bit != 0);
			bit += 23;
			switch (insn.i_format.rt & 3) {
			case 0: /* bc1f */
			case 2: /* bc1fl */
				if (~fcr31 & (1 << bit)) {
					epc = epc + 4 +
						(insn.i_format.simmediate << 2);
					if (insn.i_format.rt == 2)
						ret = BRANCH_LIKELY_TAKEN;
				} else
					epc += 8;
				regs->cp0_epc = epc;
				break;

			case 1: /* bc1t */
			case 3: /* bc1tl */
				if (fcr31 & (1 << bit)) {
					epc = epc + 4 +
						(insn.i_format.simmediate << 2);
					if (insn.i_format.rt == 3)
						ret = BRANCH_LIKELY_TAKEN;
				} else
					epc += 8;
				regs->cp0_epc = epc;
				break;
			}
			break;
		}
#ifdef CONFIG_CPU_CAVIUM_OCTEON
	case lwc2_op: /* This is bbit0 on Octeon */
		if ((regs->regs[insn.i_format.rs] & (1ull<<insn.i_format.rt))
		     == 0)
			epc = epc + 4 + (insn.i_format.simmediate << 2);
		else
			epc += 8;
		regs->cp0_epc = epc;
		break;
	case ldc2_op: /* This is bbit032 on Octeon */
		if ((regs->regs[insn.i_format.rs] &
		    (1ull<<(insn.i_format.rt+32))) == 0)
			epc = epc + 4 + (insn.i_format.simmediate << 2);
		else
			epc += 8;
		regs->cp0_epc = epc;
		break;
	case swc2_op: /* This is bbit1 on Octeon */
		if (regs->regs[insn.i_format.rs] & (1ull<<insn.i_format.rt))
			epc = epc + 4 + (insn.i_format.simmediate << 2);
		else
			epc += 8;
		regs->cp0_epc = epc;
		break;
	case sdc2_op: /* This is bbit132 on Octeon */
		if (regs->regs[insn.i_format.rs] &
		    (1ull<<(insn.i_format.rt+32)))
			epc = epc + 4 + (insn.i_format.simmediate << 2);
		else
			epc += 8;
		regs->cp0_epc = epc;
		break;
#else
	case bc6_op:
		/* Only valid for MIPS R6 */
		if (!cpu_has_mips_r6)
			goto sigill_r6;
		regs->cp0_epc += 8;
		break;
	case balc6_op:
		if (!cpu_has_mips_r6)
			goto sigill_r6;
		/* Compact branch: BALC */
		regs->regs[31] = epc + 4;
		epc += 4 + (insn.i_format.simmediate << 2);
		regs->cp0_epc = epc;
		break;
	case pop66_op:
		if (!cpu_has_mips_r6)
			goto sigill_r6;
		/* Compact branch: BEQZC || JIC */
		regs->cp0_epc += 8;
		break;
	case pop76_op:
		if (!cpu_has_mips_r6)
			goto sigill_r6;
		/* Compact branch: BNEZC || JIALC */
		if (!insn.i_format.rs) {
			/* JIALC: set $31/ra */
			regs->regs[31] = epc + 4;
		}
		regs->cp0_epc += 8;
		break;
#endif
	case pop10_op:
	case pop30_op:
		/* Only valid for MIPS R6 */
		if (!cpu_has_mips_r6)
			goto sigill_r6;
		/*
		 * Compact branches:
		 * bovc, beqc, beqzalc, bnvc, bnec, bnezlac
		 */
		if (insn.i_format.rt && !insn.i_format.rs)
			regs->regs[31] = epc + 4;
		regs->cp0_epc += 8;
		break;
	}

	return ret;

sigill_dsp:
	pr_debug("%s: DSP branch but not DSP ASE - sending SIGILL.\n",
		 current->comm);
	force_sig(SIGILL, current);
	return -EFAULT;
sigill_r2r6:
	pr_debug("%s: R2 branch but r2-to-r6 emulator is not present - sending SIGILL.\n",
		 current->comm);
	force_sig(SIGILL, current);
	return -EFAULT;
sigill_r6:
	pr_debug("%s: R6 branch but no MIPSr6 ISA support - sending SIGILL.\n",
		 current->comm);
	force_sig(SIGILL, current);
	return -EFAULT;
}