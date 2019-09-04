#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
struct TYPE_5__ {int iac1; int iac2; int dac1; int dac2; int dbcr0; int dbcr1; int dbcr2; } ;
struct TYPE_6__ {int ivpr; int epr; int csrr0; int csrr1; int dsrr0; int dsrr1; int dbsr; int tsr; int tcr; int* ivor; int mcsr; TYPE_2__ dbg_reg; TYPE_1__* shared; } ;
struct kvm_vcpu {TYPE_3__ arch; int /*<<< orphan*/  guest_debug; } ;
struct TYPE_4__ {int dar; int esr; } ;

/* Variables and functions */
 size_t BOOKE_IRQPRIO_ALIGNMENT ; 
 size_t BOOKE_IRQPRIO_AP_UNAVAIL ; 
 size_t BOOKE_IRQPRIO_CRITICAL ; 
 size_t BOOKE_IRQPRIO_DATA_STORAGE ; 
 size_t BOOKE_IRQPRIO_DEBUG ; 
 size_t BOOKE_IRQPRIO_DECREMENTER ; 
 size_t BOOKE_IRQPRIO_DTLB_MISS ; 
 size_t BOOKE_IRQPRIO_EXTERNAL ; 
 size_t BOOKE_IRQPRIO_FIT ; 
 size_t BOOKE_IRQPRIO_FP_UNAVAIL ; 
 size_t BOOKE_IRQPRIO_INST_STORAGE ; 
 size_t BOOKE_IRQPRIO_ITLB_MISS ; 
 size_t BOOKE_IRQPRIO_MACHINE_CHECK ; 
 size_t BOOKE_IRQPRIO_PROGRAM ; 
 size_t BOOKE_IRQPRIO_SYSCALL ; 
 size_t BOOKE_IRQPRIO_WATCHDOG ; 
 int DBCR0_EDM ; 
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
#define  SPRN_CSRR0 162 
#define  SPRN_CSRR1 161 
#define  SPRN_DAC1 160 
#define  SPRN_DAC2 159 
#define  SPRN_DBCR0 158 
#define  SPRN_DBCR1 157 
#define  SPRN_DBCR2 156 
#define  SPRN_DBSR 155 
#define  SPRN_DEAR 154 
#define  SPRN_DSRR0 153 
#define  SPRN_DSRR1 152 
#define  SPRN_EPR 151 
#define  SPRN_ESR 150 
#define  SPRN_IAC1 149 
#define  SPRN_IAC2 148 
#define  SPRN_IVOR0 147 
#define  SPRN_IVOR1 146 
#define  SPRN_IVOR10 145 
#define  SPRN_IVOR11 144 
#define  SPRN_IVOR12 143 
#define  SPRN_IVOR13 142 
#define  SPRN_IVOR14 141 
#define  SPRN_IVOR15 140 
#define  SPRN_IVOR2 139 
#define  SPRN_IVOR3 138 
#define  SPRN_IVOR4 137 
#define  SPRN_IVOR5 136 
#define  SPRN_IVOR6 135 
#define  SPRN_IVOR7 134 
#define  SPRN_IVOR8 133 
#define  SPRN_IVOR9 132 
#define  SPRN_IVPR 131 
#define  SPRN_MCSR 130 
#define  SPRN_TCR 129 
#define  SPRN_TSR 128 

int kvmppc_booke_emulate_mfspr(struct kvm_vcpu *vcpu, int sprn, ulong *spr_val)
{
	int emulated = EMULATE_DONE;

	switch (sprn) {
	case SPRN_IVPR:
		*spr_val = vcpu->arch.ivpr;
		break;
	case SPRN_DEAR:
		*spr_val = vcpu->arch.shared->dar;
		break;
	case SPRN_ESR:
		*spr_val = vcpu->arch.shared->esr;
		break;
	case SPRN_EPR:
		*spr_val = vcpu->arch.epr;
		break;
	case SPRN_CSRR0:
		*spr_val = vcpu->arch.csrr0;
		break;
	case SPRN_CSRR1:
		*spr_val = vcpu->arch.csrr1;
		break;
	case SPRN_DSRR0:
		*spr_val = vcpu->arch.dsrr0;
		break;
	case SPRN_DSRR1:
		*spr_val = vcpu->arch.dsrr1;
		break;
	case SPRN_IAC1:
		*spr_val = vcpu->arch.dbg_reg.iac1;
		break;
	case SPRN_IAC2:
		*spr_val = vcpu->arch.dbg_reg.iac2;
		break;
#if CONFIG_PPC_ADV_DEBUG_IACS > 2
	case SPRN_IAC3:
		*spr_val = vcpu->arch.dbg_reg.iac3;
		break;
	case SPRN_IAC4:
		*spr_val = vcpu->arch.dbg_reg.iac4;
		break;
#endif
	case SPRN_DAC1:
		*spr_val = vcpu->arch.dbg_reg.dac1;
		break;
	case SPRN_DAC2:
		*spr_val = vcpu->arch.dbg_reg.dac2;
		break;
	case SPRN_DBCR0:
		*spr_val = vcpu->arch.dbg_reg.dbcr0;
		if (vcpu->guest_debug)
			*spr_val = *spr_val | DBCR0_EDM;
		break;
	case SPRN_DBCR1:
		*spr_val = vcpu->arch.dbg_reg.dbcr1;
		break;
	case SPRN_DBCR2:
		*spr_val = vcpu->arch.dbg_reg.dbcr2;
		break;
	case SPRN_DBSR:
		*spr_val = vcpu->arch.dbsr;
		break;
	case SPRN_TSR:
		*spr_val = vcpu->arch.tsr;
		break;
	case SPRN_TCR:
		*spr_val = vcpu->arch.tcr;
		break;

	case SPRN_IVOR0:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_CRITICAL];
		break;
	case SPRN_IVOR1:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_MACHINE_CHECK];
		break;
	case SPRN_IVOR2:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_DATA_STORAGE];
		break;
	case SPRN_IVOR3:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_INST_STORAGE];
		break;
	case SPRN_IVOR4:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_EXTERNAL];
		break;
	case SPRN_IVOR5:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_ALIGNMENT];
		break;
	case SPRN_IVOR6:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_PROGRAM];
		break;
	case SPRN_IVOR7:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_FP_UNAVAIL];
		break;
	case SPRN_IVOR8:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_SYSCALL];
		break;
	case SPRN_IVOR9:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_AP_UNAVAIL];
		break;
	case SPRN_IVOR10:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_DECREMENTER];
		break;
	case SPRN_IVOR11:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_FIT];
		break;
	case SPRN_IVOR12:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_WATCHDOG];
		break;
	case SPRN_IVOR13:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_DTLB_MISS];
		break;
	case SPRN_IVOR14:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_ITLB_MISS];
		break;
	case SPRN_IVOR15:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_DEBUG];
		break;
	case SPRN_MCSR:
		*spr_val = vcpu->arch.mcsr;
		break;
#if defined(CONFIG_64BIT)
	case SPRN_EPCR:
		*spr_val = vcpu->arch.epcr;
		break;
#endif

	default:
		emulated = EMULATE_FAIL;
	}

	return emulated;
}