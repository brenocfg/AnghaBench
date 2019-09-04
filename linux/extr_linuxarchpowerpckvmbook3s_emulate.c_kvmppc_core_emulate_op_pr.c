#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long ulong ;
typedef  unsigned long long u32 ;
struct TYPE_3__ {unsigned long long (* mfsrin ) (struct kvm_vcpu*,int) ;unsigned long long (* slbmfee ) (struct kvm_vcpu*,unsigned long long) ;unsigned long long (* slbmfev ) (struct kvm_vcpu*,unsigned long long) ;int /*<<< orphan*/  (* slbia ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* slbie ) (struct kvm_vcpu*,int) ;int /*<<< orphan*/  (* slbmte ) (struct kvm_vcpu*,int,int) ;int /*<<< orphan*/  (* tlbie ) (struct kvm_vcpu*,unsigned long long,int) ;int /*<<< orphan*/  (* mtsrin ) (struct kvm_vcpu*,int,int) ;} ;
struct TYPE_4__ {unsigned long long fault_dar; unsigned long long fault_dsisr; TYPE_1__ mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct kvm_run {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOK3S_INTERRUPT_DATA_STORAGE ; 
 unsigned long long DSISR_ISSTORE ; 
 unsigned long long DSISR_NOHPTE ; 
 unsigned long long DSISR_PROTFAULT ; 
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
 int ENOENT ; 
 int EPERM ; 
 unsigned long long EV_UNIMPLEMENTED ; 
 unsigned long long MSR_EE ; 
 unsigned long long MSR_LE ; 
 unsigned long long MSR_RI ; 
 unsigned long long MSR_SF ; 
#define  OP_19_XOP_RFI 146 
#define  OP_19_XOP_RFID 145 
#define  OP_31_XOP_DCBA 144 
#define  OP_31_XOP_DCBZ 143 
#define  OP_31_XOP_EIOIO 142 
#define  OP_31_XOP_MFMSR 141 
#define  OP_31_XOP_MFSR 140 
#define  OP_31_XOP_MFSRIN 139 
#define  OP_31_XOP_MTMSR 138 
#define  OP_31_XOP_MTMSRD 137 
#define  OP_31_XOP_MTSR 136 
#define  OP_31_XOP_MTSRIN 135 
#define  OP_31_XOP_SLBIA 134 
#define  OP_31_XOP_SLBIE 133 
#define  OP_31_XOP_SLBMFEE 132 
#define  OP_31_XOP_SLBMFEV 131 
#define  OP_31_XOP_SLBMTE 130 
#define  OP_31_XOP_TLBIE 129 
#define  OP_31_XOP_TLBIEL 128 
 int get_op (unsigned int) ; 
 int get_ra (unsigned int) ; 
 int get_rb (unsigned int) ; 
 int get_rs (unsigned int) ; 
 int get_rt (unsigned int) ; 
 int /*<<< orphan*/  get_xop (unsigned int) ; 
 int /*<<< orphan*/  kvmppc_book3s_queue_irqprio (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvmppc_emulate_paired_single (struct kvm_run*,struct kvm_vcpu*) ; 
 int kvmppc_get_field (unsigned int,int,int) ; 
 int kvmppc_get_gpr (struct kvm_vcpu*,int) ; 
 unsigned long long kvmppc_get_msr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_pc (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_srr0 (struct kvm_vcpu*) ; 
 unsigned long kvmppc_get_srr1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_dar (struct kvm_vcpu*,unsigned long long) ; 
 int /*<<< orphan*/  kvmppc_set_dsisr (struct kvm_vcpu*,unsigned long long) ; 
 int /*<<< orphan*/  kvmppc_set_gpr (struct kvm_vcpu*,int,unsigned long long) ; 
 int /*<<< orphan*/  kvmppc_set_msr (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_set_msr_fast (struct kvm_vcpu*,unsigned long long) ; 
 int /*<<< orphan*/  kvmppc_set_pc (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvmppc_st (struct kvm_vcpu*,unsigned long long*,int,unsigned long long*,int) ; 
 unsigned long long stub1 (struct kvm_vcpu*,int) ; 
 unsigned long long stub10 (struct kvm_vcpu*,unsigned long long) ; 
 unsigned long long stub2 (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  stub3 (struct kvm_vcpu*,unsigned int,int) ; 
 int /*<<< orphan*/  stub4 (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct kvm_vcpu*,unsigned long long,int) ; 
 int /*<<< orphan*/  stub6 (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  stub7 (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  stub8 (struct kvm_vcpu*) ; 
 unsigned long long stub9 (struct kvm_vcpu*,unsigned long long) ; 
 unsigned int swab32 (unsigned long long) ; 

int kvmppc_core_emulate_op_pr(struct kvm_run *run, struct kvm_vcpu *vcpu,
			      unsigned int inst, int *advance)
{
	int emulated = EMULATE_DONE;
	int rt = get_rt(inst);
	int rs = get_rs(inst);
	int ra = get_ra(inst);
	int rb = get_rb(inst);
	u32 inst_sc = 0x44000002;

	switch (get_op(inst)) {
	case 0:
		emulated = EMULATE_FAIL;
		if ((kvmppc_get_msr(vcpu) & MSR_LE) &&
		    (inst == swab32(inst_sc))) {
			/*
			 * This is the byte reversed syscall instruction of our
			 * hypercall handler. Early versions of LE Linux didn't
			 * swap the instructions correctly and ended up in
			 * illegal instructions.
			 * Just always fail hypercalls on these broken systems.
			 */
			kvmppc_set_gpr(vcpu, 3, EV_UNIMPLEMENTED);
			kvmppc_set_pc(vcpu, kvmppc_get_pc(vcpu) + 4);
			emulated = EMULATE_DONE;
		}
		break;
	case 19:
		switch (get_xop(inst)) {
		case OP_19_XOP_RFID:
		case OP_19_XOP_RFI: {
			unsigned long srr1 = kvmppc_get_srr1(vcpu);
#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
			unsigned long cur_msr = kvmppc_get_msr(vcpu);

			/*
			 * add rules to fit in ISA specification regarding TM
			 * state transistion in TM disable/Suspended state,
			 * and target TM state is TM inactive(00) state. (the
			 * change should be suppressed).
			 */
			if (((cur_msr & MSR_TM) == 0) &&
				((srr1 & MSR_TM) == 0) &&
				MSR_TM_SUSPENDED(cur_msr) &&
				!MSR_TM_ACTIVE(srr1))
				srr1 |= MSR_TS_S;
#endif
			kvmppc_set_pc(vcpu, kvmppc_get_srr0(vcpu));
			kvmppc_set_msr(vcpu, srr1);
			*advance = 0;
			break;
		}

		default:
			emulated = EMULATE_FAIL;
			break;
		}
		break;
	case 31:
		switch (get_xop(inst)) {
		case OP_31_XOP_MFMSR:
			kvmppc_set_gpr(vcpu, rt, kvmppc_get_msr(vcpu));
			break;
		case OP_31_XOP_MTMSRD:
		{
			ulong rs_val = kvmppc_get_gpr(vcpu, rs);
			if (inst & 0x10000) {
				ulong new_msr = kvmppc_get_msr(vcpu);
				new_msr &= ~(MSR_RI | MSR_EE);
				new_msr |= rs_val & (MSR_RI | MSR_EE);
				kvmppc_set_msr_fast(vcpu, new_msr);
			} else
				kvmppc_set_msr(vcpu, rs_val);
			break;
		}
		case OP_31_XOP_MTMSR:
			kvmppc_set_msr(vcpu, kvmppc_get_gpr(vcpu, rs));
			break;
		case OP_31_XOP_MFSR:
		{
			int srnum;

			srnum = kvmppc_get_field(inst, 12 + 32, 15 + 32);
			if (vcpu->arch.mmu.mfsrin) {
				u32 sr;
				sr = vcpu->arch.mmu.mfsrin(vcpu, srnum);
				kvmppc_set_gpr(vcpu, rt, sr);
			}
			break;
		}
		case OP_31_XOP_MFSRIN:
		{
			int srnum;

			srnum = (kvmppc_get_gpr(vcpu, rb) >> 28) & 0xf;
			if (vcpu->arch.mmu.mfsrin) {
				u32 sr;
				sr = vcpu->arch.mmu.mfsrin(vcpu, srnum);
				kvmppc_set_gpr(vcpu, rt, sr);
			}
			break;
		}
		case OP_31_XOP_MTSR:
			vcpu->arch.mmu.mtsrin(vcpu,
				(inst >> 16) & 0xf,
				kvmppc_get_gpr(vcpu, rs));
			break;
		case OP_31_XOP_MTSRIN:
			vcpu->arch.mmu.mtsrin(vcpu,
				(kvmppc_get_gpr(vcpu, rb) >> 28) & 0xf,
				kvmppc_get_gpr(vcpu, rs));
			break;
		case OP_31_XOP_TLBIE:
		case OP_31_XOP_TLBIEL:
		{
			bool large = (inst & 0x00200000) ? true : false;
			ulong addr = kvmppc_get_gpr(vcpu, rb);
			vcpu->arch.mmu.tlbie(vcpu, addr, large);
			break;
		}
#ifdef CONFIG_PPC_BOOK3S_64
		case OP_31_XOP_FAKE_SC1:
		{
			/* SC 1 papr hypercalls */
			ulong cmd = kvmppc_get_gpr(vcpu, 3);
			int i;

		        if ((kvmppc_get_msr(vcpu) & MSR_PR) ||
			    !vcpu->arch.papr_enabled) {
				emulated = EMULATE_FAIL;
				break;
			}

			if (kvmppc_h_pr(vcpu, cmd) == EMULATE_DONE)
				break;

			run->papr_hcall.nr = cmd;
			for (i = 0; i < 9; ++i) {
				ulong gpr = kvmppc_get_gpr(vcpu, 4 + i);
				run->papr_hcall.args[i] = gpr;
			}

			run->exit_reason = KVM_EXIT_PAPR_HCALL;
			vcpu->arch.hcall_needed = 1;
			emulated = EMULATE_EXIT_USER;
			break;
		}
#endif
		case OP_31_XOP_EIOIO:
			break;
		case OP_31_XOP_SLBMTE:
			if (!vcpu->arch.mmu.slbmte)
				return EMULATE_FAIL;

			vcpu->arch.mmu.slbmte(vcpu,
					kvmppc_get_gpr(vcpu, rs),
					kvmppc_get_gpr(vcpu, rb));
			break;
		case OP_31_XOP_SLBIE:
			if (!vcpu->arch.mmu.slbie)
				return EMULATE_FAIL;

			vcpu->arch.mmu.slbie(vcpu,
					kvmppc_get_gpr(vcpu, rb));
			break;
		case OP_31_XOP_SLBIA:
			if (!vcpu->arch.mmu.slbia)
				return EMULATE_FAIL;

			vcpu->arch.mmu.slbia(vcpu);
			break;
		case OP_31_XOP_SLBMFEE:
			if (!vcpu->arch.mmu.slbmfee) {
				emulated = EMULATE_FAIL;
			} else {
				ulong t, rb_val;

				rb_val = kvmppc_get_gpr(vcpu, rb);
				t = vcpu->arch.mmu.slbmfee(vcpu, rb_val);
				kvmppc_set_gpr(vcpu, rt, t);
			}
			break;
		case OP_31_XOP_SLBMFEV:
			if (!vcpu->arch.mmu.slbmfev) {
				emulated = EMULATE_FAIL;
			} else {
				ulong t, rb_val;

				rb_val = kvmppc_get_gpr(vcpu, rb);
				t = vcpu->arch.mmu.slbmfev(vcpu, rb_val);
				kvmppc_set_gpr(vcpu, rt, t);
			}
			break;
		case OP_31_XOP_DCBA:
			/* Gets treated as NOP */
			break;
		case OP_31_XOP_DCBZ:
		{
			ulong rb_val = kvmppc_get_gpr(vcpu, rb);
			ulong ra_val = 0;
			ulong addr, vaddr;
			u32 zeros[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
			u32 dsisr;
			int r;

			if (ra)
				ra_val = kvmppc_get_gpr(vcpu, ra);

			addr = (ra_val + rb_val) & ~31ULL;
			if (!(kvmppc_get_msr(vcpu) & MSR_SF))
				addr &= 0xffffffff;
			vaddr = addr;

			r = kvmppc_st(vcpu, &addr, 32, zeros, true);
			if ((r == -ENOENT) || (r == -EPERM)) {
				*advance = 0;
				kvmppc_set_dar(vcpu, vaddr);
				vcpu->arch.fault_dar = vaddr;

				dsisr = DSISR_ISSTORE;
				if (r == -ENOENT)
					dsisr |= DSISR_NOHPTE;
				else if (r == -EPERM)
					dsisr |= DSISR_PROTFAULT;

				kvmppc_set_dsisr(vcpu, dsisr);
				vcpu->arch.fault_dsisr = dsisr;

				kvmppc_book3s_queue_irqprio(vcpu,
					BOOK3S_INTERRUPT_DATA_STORAGE);
			}

			break;
		}
#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
		case OP_31_XOP_TBEGIN:
		{
			if (!cpu_has_feature(CPU_FTR_TM))
				break;

			if (!(kvmppc_get_msr(vcpu) & MSR_TM)) {
				kvmppc_trigger_fac_interrupt(vcpu, FSCR_TM_LG);
				emulated = EMULATE_AGAIN;
				break;
			}

			if (!(kvmppc_get_msr(vcpu) & MSR_PR)) {
				preempt_disable();
				vcpu->arch.cr = (CR0_TBEGIN_FAILURE |
				  (vcpu->arch.cr & ~(CR0_MASK << CR0_SHIFT)));

				vcpu->arch.texasr = (TEXASR_FS | TEXASR_EXACT |
					(((u64)(TM_CAUSE_EMULATE | TM_CAUSE_PERSISTENT))
						 << TEXASR_FC_LG));

				if ((inst >> 21) & 0x1)
					vcpu->arch.texasr |= TEXASR_ROT;

				if (kvmppc_get_msr(vcpu) & MSR_HV)
					vcpu->arch.texasr |= TEXASR_HV;

				vcpu->arch.tfhar = kvmppc_get_pc(vcpu) + 4;
				vcpu->arch.tfiar = kvmppc_get_pc(vcpu);

				kvmppc_restore_tm_sprs(vcpu);
				preempt_enable();
			} else
				emulated = EMULATE_FAIL;
			break;
		}
		case OP_31_XOP_TABORT:
		{
			ulong guest_msr = kvmppc_get_msr(vcpu);
			unsigned long ra_val = 0;

			if (!cpu_has_feature(CPU_FTR_TM))
				break;

			if (!(kvmppc_get_msr(vcpu) & MSR_TM)) {
				kvmppc_trigger_fac_interrupt(vcpu, FSCR_TM_LG);
				emulated = EMULATE_AGAIN;
				break;
			}

			/* only emulate for privilege guest, since problem state
			 * guest can run with TM enabled and we don't expect to
			 * trap at here for that case.
			 */
			WARN_ON(guest_msr & MSR_PR);

			if (ra)
				ra_val = kvmppc_get_gpr(vcpu, ra);

			kvmppc_emulate_tabort(vcpu, ra_val);
			break;
		}
		case OP_31_XOP_TRECLAIM:
		{
			ulong guest_msr = kvmppc_get_msr(vcpu);
			unsigned long ra_val = 0;

			if (!cpu_has_feature(CPU_FTR_TM))
				break;

			if (!(kvmppc_get_msr(vcpu) & MSR_TM)) {
				kvmppc_trigger_fac_interrupt(vcpu, FSCR_TM_LG);
				emulated = EMULATE_AGAIN;
				break;
			}

			/* generate interrupts based on priorities */
			if (guest_msr & MSR_PR) {
				/* Privileged Instruction type Program Interrupt */
				kvmppc_core_queue_program(vcpu, SRR1_PROGPRIV);
				emulated = EMULATE_AGAIN;
				break;
			}

			if (!MSR_TM_ACTIVE(guest_msr)) {
				/* TM bad thing interrupt */
				kvmppc_core_queue_program(vcpu, SRR1_PROGTM);
				emulated = EMULATE_AGAIN;
				break;
			}

			if (ra)
				ra_val = kvmppc_get_gpr(vcpu, ra);
			kvmppc_emulate_treclaim(vcpu, ra_val);
			break;
		}
		case OP_31_XOP_TRCHKPT:
		{
			ulong guest_msr = kvmppc_get_msr(vcpu);
			unsigned long texasr;

			if (!cpu_has_feature(CPU_FTR_TM))
				break;

			if (!(kvmppc_get_msr(vcpu) & MSR_TM)) {
				kvmppc_trigger_fac_interrupt(vcpu, FSCR_TM_LG);
				emulated = EMULATE_AGAIN;
				break;
			}

			/* generate interrupt based on priorities */
			if (guest_msr & MSR_PR) {
				/* Privileged Instruction type Program Intr */
				kvmppc_core_queue_program(vcpu, SRR1_PROGPRIV);
				emulated = EMULATE_AGAIN;
				break;
			}

			tm_enable();
			texasr = mfspr(SPRN_TEXASR);
			tm_disable();

			if (MSR_TM_ACTIVE(guest_msr) ||
				!(texasr & (TEXASR_FS))) {
				/* TM bad thing interrupt */
				kvmppc_core_queue_program(vcpu, SRR1_PROGTM);
				emulated = EMULATE_AGAIN;
				break;
			}

			kvmppc_emulate_trchkpt(vcpu);
			break;
		}
#endif
		default:
			emulated = EMULATE_FAIL;
		}
		break;
	default:
		emulated = EMULATE_FAIL;
	}

	if (emulated == EMULATE_FAIL)
		emulated = kvmppc_emulate_paired_single(run, vcpu);

	return emulated;
}