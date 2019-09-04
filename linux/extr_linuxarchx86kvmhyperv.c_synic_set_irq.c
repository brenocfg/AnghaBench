#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu_hv_synic {int /*<<< orphan*/  sint; } ;
struct TYPE_2__ {int /*<<< orphan*/  apic; } ;
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;
struct kvm_lapic_irq {int vector; int level; int /*<<< orphan*/  delivery_mode; int /*<<< orphan*/  dest_mode; int /*<<< orphan*/  shorthand; } ;
typedef  int /*<<< orphan*/  irq ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DEST_PHYSICAL ; 
 int /*<<< orphan*/  APIC_DEST_SELF ; 
 int /*<<< orphan*/  APIC_DM_FIXED ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOENT ; 
 int kvm_irq_delivery_to_apic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvm_lapic_irq*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct kvm_lapic_irq*,int /*<<< orphan*/ ,int) ; 
 int synic_get_sint_vector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synic_read_sint (struct kvm_vcpu_hv_synic*,int /*<<< orphan*/ ) ; 
 struct kvm_vcpu* synic_to_vcpu (struct kvm_vcpu_hv_synic*) ; 
 int /*<<< orphan*/  trace_kvm_hv_synic_set_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int synic_set_irq(struct kvm_vcpu_hv_synic *synic, u32 sint)
{
	struct kvm_vcpu *vcpu = synic_to_vcpu(synic);
	struct kvm_lapic_irq irq;
	int ret, vector;

	if (sint >= ARRAY_SIZE(synic->sint))
		return -EINVAL;

	vector = synic_get_sint_vector(synic_read_sint(synic, sint));
	if (vector < 0)
		return -ENOENT;

	memset(&irq, 0, sizeof(irq));
	irq.shorthand = APIC_DEST_SELF;
	irq.dest_mode = APIC_DEST_PHYSICAL;
	irq.delivery_mode = APIC_DM_FIXED;
	irq.vector = vector;
	irq.level = 1;

	ret = kvm_irq_delivery_to_apic(vcpu->kvm, vcpu->arch.apic, &irq, NULL);
	trace_kvm_hv_synic_set_irq(vcpu->vcpu_id, sint, irq.vector, ret);
	return ret;
}