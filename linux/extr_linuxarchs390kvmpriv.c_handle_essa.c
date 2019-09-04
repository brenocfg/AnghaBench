#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_6__* sie_block; struct gmap* gmap; } ;
struct TYPE_10__ {int /*<<< orphan*/  instruction_essa; } ;
struct kvm_vcpu {TYPE_7__ arch; TYPE_9__* kvm; TYPE_1__ stat; } ;
struct gmap {TYPE_8__* mm; } ;
struct TYPE_12__ {int /*<<< orphan*/  migration_mode; int /*<<< orphan*/  use_cmma; } ;
struct TYPE_18__ {TYPE_5__* mm; int /*<<< orphan*/  srcu; TYPE_3__ arch; } ;
struct TYPE_17__ {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_11__ {int mask; } ;
struct TYPE_15__ {int cbrlo; int ipb; int /*<<< orphan*/  ecb2; TYPE_2__ gpsw; } ;
struct TYPE_13__ {int uses_cmm; } ;
struct TYPE_14__ {int /*<<< orphan*/  mmap_sem; TYPE_4__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECB2_CMMA ; 
 int ESSA_SET_STABLE_IF_RESIDENT ; 
 int ESSA_SET_STABLE_NODAT ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  PGM_OPERATION ; 
 int /*<<< orphan*/  PGM_PRIVILEGED_OP ; 
 int /*<<< orphan*/  PGM_SPECIFICATION ; 
 int PSW_MASK_PSTATE ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,int) ; 
 int __do_essa (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  __gmap_zap (struct gmap*,unsigned long) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_retry_instr (struct kvm_vcpu*) ; 
 unsigned long* phys_to_virt (int) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 scalar_t__ test_kvm_facility (TYPE_9__*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_essa(struct kvm_vcpu *vcpu)
{
	/* entries expected to be 1FF */
	int entries = (vcpu->arch.sie_block->cbrlo & ~PAGE_MASK) >> 3;
	unsigned long *cbrlo;
	struct gmap *gmap;
	int i, orc;

	VCPU_EVENT(vcpu, 4, "ESSA: release %d pages", entries);
	gmap = vcpu->arch.gmap;
	vcpu->stat.instruction_essa++;
	if (!vcpu->kvm->arch.use_cmma)
		return kvm_s390_inject_program_int(vcpu, PGM_OPERATION);

	if (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		return kvm_s390_inject_program_int(vcpu, PGM_PRIVILEGED_OP);
	/* Check for invalid operation request code */
	orc = (vcpu->arch.sie_block->ipb & 0xf0000000) >> 28;
	/* ORCs 0-6 are always valid */
	if (orc > (test_kvm_facility(vcpu->kvm, 147) ? ESSA_SET_STABLE_NODAT
						: ESSA_SET_STABLE_IF_RESIDENT))
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

	if (!vcpu->kvm->arch.migration_mode) {
		/*
		 * CMMA is enabled in the KVM settings, but is disabled in
		 * the SIE block and in the mm_context, and we are not doing
		 * a migration. Enable CMMA in the mm_context.
		 * Since we need to take a write lock to write to the context
		 * to avoid races with storage keys handling, we check if the
		 * value really needs to be written to; if the value is
		 * already correct, we do nothing and avoid the lock.
		 */
		if (vcpu->kvm->mm->context.uses_cmm == 0) {
			down_write(&vcpu->kvm->mm->mmap_sem);
			vcpu->kvm->mm->context.uses_cmm = 1;
			up_write(&vcpu->kvm->mm->mmap_sem);
		}
		/*
		 * If we are here, we are supposed to have CMMA enabled in
		 * the SIE block. Enabling CMMA works on a per-CPU basis,
		 * while the context use_cmma flag is per process.
		 * It's possible that the context flag is enabled and the
		 * SIE flag is not, so we set the flag always; if it was
		 * already set, nothing changes, otherwise we enable it
		 * on this CPU too.
		 */
		vcpu->arch.sie_block->ecb2 |= ECB2_CMMA;
		/* Retry the ESSA instruction */
		kvm_s390_retry_instr(vcpu);
	} else {
		int srcu_idx;

		down_read(&vcpu->kvm->mm->mmap_sem);
		srcu_idx = srcu_read_lock(&vcpu->kvm->srcu);
		i = __do_essa(vcpu, orc);
		srcu_read_unlock(&vcpu->kvm->srcu, srcu_idx);
		up_read(&vcpu->kvm->mm->mmap_sem);
		if (i < 0)
			return i;
		/* Account for the possible extra cbrl entry */
		entries += i;
	}
	vcpu->arch.sie_block->cbrlo &= PAGE_MASK;	/* reset nceo */
	cbrlo = phys_to_virt(vcpu->arch.sie_block->cbrlo);
	down_read(&gmap->mm->mmap_sem);
	for (i = 0; i < entries; ++i)
		__gmap_zap(gmap, cbrlo[i]);
	up_read(&gmap->mm->mmap_sem);
	return 0;
}