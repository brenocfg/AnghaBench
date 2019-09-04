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
struct pt_regs {int msr; unsigned long dar; int* gpr; void* nip; } ;
struct instruction_op {int type; size_t reg; unsigned long val; void* ea; } ;

/* Variables and functions */
#define  CACHEOP 136 
 int CACHEOP_MASK ; 
#define  DCBF 135 
#define  DCBST 134 
#define  DCBT 133 
#define  DCBTST 132 
#define  DCBZ 131 
 int GETTYPE (int) ; 
#define  ICBI 130 
#define  MFMSR 129 
 int MSR_MASK ; 
 unsigned long MSR_RI ; 
#define  MTMSR 128 
 scalar_t__ OP_IS_LOAD_STORE (int) ; 
 int /*<<< orphan*/  __cacheop_user_asmx (unsigned long,int,char*) ; 
 int /*<<< orphan*/  address_ok (struct pt_regs*,unsigned long,int) ; 
 int analyse_instr (struct instruction_op*,struct pt_regs*,unsigned int) ; 
 int emulate_dcbz (unsigned long,struct pt_regs*) ; 
 int emulate_loadstore (struct pt_regs*,struct instruction_op*) ; 
 int /*<<< orphan*/  emulate_update_regs (struct pt_regs*,struct instruction_op*) ; 
 int /*<<< orphan*/  prefetch (void*) ; 
 int /*<<< orphan*/  prefetchw (void*) ; 
 void* truncate_if_32bit (int,void*) ; 

int emulate_step(struct pt_regs *regs, unsigned int instr)
{
	struct instruction_op op;
	int r, err, type;
	unsigned long val;
	unsigned long ea;

	r = analyse_instr(&op, regs, instr);
	if (r < 0)
		return r;
	if (r > 0) {
		emulate_update_regs(regs, &op);
		return 1;
	}

	err = 0;
	type = GETTYPE(op.type);

	if (OP_IS_LOAD_STORE(type)) {
		err = emulate_loadstore(regs, &op);
		if (err)
			return 0;
		goto instr_done;
	}

	switch (type) {
	case CACHEOP:
		ea = truncate_if_32bit(regs->msr, op.ea);
		if (!address_ok(regs, ea, 8))
			return 0;
		switch (op.type & CACHEOP_MASK) {
		case DCBST:
			__cacheop_user_asmx(ea, err, "dcbst");
			break;
		case DCBF:
			__cacheop_user_asmx(ea, err, "dcbf");
			break;
		case DCBTST:
			if (op.reg == 0)
				prefetchw((void *) ea);
			break;
		case DCBT:
			if (op.reg == 0)
				prefetch((void *) ea);
			break;
		case ICBI:
			__cacheop_user_asmx(ea, err, "icbi");
			break;
		case DCBZ:
			err = emulate_dcbz(ea, regs);
			break;
		}
		if (err) {
			regs->dar = ea;
			return 0;
		}
		goto instr_done;

	case MFMSR:
		regs->gpr[op.reg] = regs->msr & MSR_MASK;
		goto instr_done;

	case MTMSR:
		val = regs->gpr[op.reg];
		if ((val & MSR_RI) == 0)
			/* can't step mtmsr[d] that would clear MSR_RI */
			return -1;
		/* here op.val is the mask of bits to change */
		regs->msr = (regs->msr & ~op.val) | (val & op.val);
		goto instr_done;

#ifdef CONFIG_PPC64
	case SYSCALL:	/* sc */
		/*
		 * N.B. this uses knowledge about how the syscall
		 * entry code works.  If that is changed, this will
		 * need to be changed also.
		 */
		if (regs->gpr[0] == 0x1ebe &&
		    cpu_has_feature(CPU_FTR_REAL_LE)) {
			regs->msr ^= MSR_LE;
			goto instr_done;
		}
		regs->gpr[9] = regs->gpr[13];
		regs->gpr[10] = MSR_KERNEL;
		regs->gpr[11] = regs->nip + 4;
		regs->gpr[12] = regs->msr & MSR_MASK;
		regs->gpr[13] = (unsigned long) get_paca();
		regs->nip = (unsigned long) &system_call_common;
		regs->msr = MSR_KERNEL;
		return 1;

	case RFI:
		return -1;
#endif
	}
	return 0;

 instr_done:
	regs->nip = truncate_if_32bit(regs->msr, regs->nip + 4);
	return 1;
}