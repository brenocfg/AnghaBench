#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct lppaca {void* dtl_idx; } ;
struct kvmppc_vcore {scalar_t__ tb_offset; scalar_t__ pcpu; } ;
struct TYPE_7__ {int dirty; struct dtl_entry* pinned_addr; struct dtl_entry* pinned_end; } ;
struct TYPE_6__ {scalar_t__ msr; } ;
struct TYPE_5__ {struct lppaca* pinned_addr; } ;
struct TYPE_8__ {unsigned long stolen_logged; TYPE_3__ dtl; scalar_t__ dtl_index; struct dtl_entry* dtl_ptr; TYPE_2__ shregs; scalar_t__ ptid; int /*<<< orphan*/  tbacct_lock; scalar_t__ busy_stolen; TYPE_1__ vpa; } ;
struct kvm_vcpu {TYPE_4__ arch; } ;
struct dtl_entry {int dispatch_reason; void* srr1; void* srr0; int /*<<< orphan*/  enqueue_to_dispatch_time; void* timebase; int /*<<< orphan*/  processor_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned long) ; 
 void* cpu_to_be64 (scalar_t__) ; 
 scalar_t__ kvmppc_get_pc (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  memset (struct dtl_entry*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mftb () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long vcore_stolen_time (struct kvmppc_vcore*,scalar_t__) ; 

__attribute__((used)) static void kvmppc_create_dtl_entry(struct kvm_vcpu *vcpu,
				    struct kvmppc_vcore *vc)
{
	struct dtl_entry *dt;
	struct lppaca *vpa;
	unsigned long stolen;
	unsigned long core_stolen;
	u64 now;
	unsigned long flags;

	dt = vcpu->arch.dtl_ptr;
	vpa = vcpu->arch.vpa.pinned_addr;
	now = mftb();
	core_stolen = vcore_stolen_time(vc, now);
	stolen = core_stolen - vcpu->arch.stolen_logged;
	vcpu->arch.stolen_logged = core_stolen;
	spin_lock_irqsave(&vcpu->arch.tbacct_lock, flags);
	stolen += vcpu->arch.busy_stolen;
	vcpu->arch.busy_stolen = 0;
	spin_unlock_irqrestore(&vcpu->arch.tbacct_lock, flags);
	if (!dt || !vpa)
		return;
	memset(dt, 0, sizeof(struct dtl_entry));
	dt->dispatch_reason = 7;
	dt->processor_id = cpu_to_be16(vc->pcpu + vcpu->arch.ptid);
	dt->timebase = cpu_to_be64(now + vc->tb_offset);
	dt->enqueue_to_dispatch_time = cpu_to_be32(stolen);
	dt->srr0 = cpu_to_be64(kvmppc_get_pc(vcpu));
	dt->srr1 = cpu_to_be64(vcpu->arch.shregs.msr);
	++dt;
	if (dt == vcpu->arch.dtl.pinned_end)
		dt = vcpu->arch.dtl.pinned_addr;
	vcpu->arch.dtl_ptr = dt;
	/* order writing *dt vs. writing vpa->dtl_idx */
	smp_wmb();
	vpa->dtl_idx = cpu_to_be64(++vcpu->arch.dtl_index);
	vcpu->arch.dtl.dirty = true;
}