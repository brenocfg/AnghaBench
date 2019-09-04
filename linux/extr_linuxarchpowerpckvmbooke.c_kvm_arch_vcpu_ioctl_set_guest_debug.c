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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct debug_reg {int dbcr0; int dbcr1; int dbcr2; } ;
struct TYPE_4__ {struct debug_reg dbg_reg; } ;
struct kvm_vcpu {int guest_debug; TYPE_1__ arch; } ;
struct TYPE_6__ {TYPE_2__* bp; } ;
struct kvm_guest_debug {int control; TYPE_3__ arch; } ;
struct TYPE_5__ {int type; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int DBCR0_IC ; 
 int DBCR0_IDM ; 
 int DBCR1_IAC1US ; 
 int DBCR1_IAC2US ; 
 int DBCR1_IAC3US ; 
 int DBCR1_IAC4US ; 
 int DBCR2_DAC1US ; 
 int DBCR2_DAC2US ; 
 int EINVAL ; 
 int KVMPPC_BOOKE_DAC_NUM ; 
 int KVMPPC_BOOKE_IAC_NUM ; 
 int KVMPPC_DEBUG_BREAKPOINT ; 
 int KVMPPC_DEBUG_NONE ; 
 int KVMPPC_DEBUG_WATCH_READ ; 
 int KVMPPC_DEBUG_WATCH_WRITE ; 
 int KVM_GUESTDBG_ENABLE ; 
 int KVM_GUESTDBG_SINGLESTEP ; 
 int KVM_GUESTDBG_USE_HW_BP ; 
 int /*<<< orphan*/  MSR_DE ; 
 int /*<<< orphan*/  kvm_guest_protect_msr (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kvmppc_booke_add_breakpoint (struct debug_reg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kvmppc_booke_add_watchpoint (struct debug_reg*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_set_guest_debug(struct kvm_vcpu *vcpu,
					 struct kvm_guest_debug *dbg)
{
	struct debug_reg *dbg_reg;
	int n, b = 0, w = 0;
	int ret = 0;

	vcpu_load(vcpu);

	if (!(dbg->control & KVM_GUESTDBG_ENABLE)) {
		vcpu->arch.dbg_reg.dbcr0 = 0;
		vcpu->guest_debug = 0;
		kvm_guest_protect_msr(vcpu, MSR_DE, false);
		goto out;
	}

	kvm_guest_protect_msr(vcpu, MSR_DE, true);
	vcpu->guest_debug = dbg->control;
	vcpu->arch.dbg_reg.dbcr0 = 0;

	if (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP)
		vcpu->arch.dbg_reg.dbcr0 |= DBCR0_IDM | DBCR0_IC;

	/* Code below handles only HW breakpoints */
	dbg_reg = &(vcpu->arch.dbg_reg);

#ifdef CONFIG_KVM_BOOKE_HV
	/*
	 * On BookE-HV (e500mc) the guest is always executed with MSR.GS=1
	 * DBCR1 and DBCR2 are set to trigger debug events when MSR.PR is 0
	 */
	dbg_reg->dbcr1 = 0;
	dbg_reg->dbcr2 = 0;
#else
	/*
	 * On BookE-PR (e500v2) the guest is always executed with MSR.PR=1
	 * We set DBCR1 and DBCR2 to only trigger debug events when MSR.PR
	 * is set.
	 */
	dbg_reg->dbcr1 = DBCR1_IAC1US | DBCR1_IAC2US | DBCR1_IAC3US |
			  DBCR1_IAC4US;
	dbg_reg->dbcr2 = DBCR2_DAC1US | DBCR2_DAC2US;
#endif

	if (!(vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP))
		goto out;

	ret = -EINVAL;
	for (n = 0; n < (KVMPPC_BOOKE_IAC_NUM + KVMPPC_BOOKE_DAC_NUM); n++) {
		uint64_t addr = dbg->arch.bp[n].addr;
		uint32_t type = dbg->arch.bp[n].type;

		if (type == KVMPPC_DEBUG_NONE)
			continue;

		if (type & ~(KVMPPC_DEBUG_WATCH_READ |
			     KVMPPC_DEBUG_WATCH_WRITE |
			     KVMPPC_DEBUG_BREAKPOINT))
			goto out;

		if (type & KVMPPC_DEBUG_BREAKPOINT) {
			/* Setting H/W breakpoint */
			if (kvmppc_booke_add_breakpoint(dbg_reg, addr, b++))
				goto out;
		} else {
			/* Setting H/W watchpoint */
			if (kvmppc_booke_add_watchpoint(dbg_reg, addr,
							type, w++))
				goto out;
		}
	}

	ret = 0;
out:
	vcpu_put(vcpu);
	return ret;
}