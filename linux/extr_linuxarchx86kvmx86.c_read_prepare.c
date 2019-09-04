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
struct kvm_vcpu {scalar_t__ mmio_read_completed; TYPE_1__* mmio_fragments; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpa; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_TRACE_MMIO_READ ; 
 int /*<<< orphan*/  trace_kvm_mmio (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int read_prepare(struct kvm_vcpu *vcpu, void *val, int bytes)
{
	if (vcpu->mmio_read_completed) {
		trace_kvm_mmio(KVM_TRACE_MMIO_READ, bytes,
			       vcpu->mmio_fragments[0].gpa, val);
		vcpu->mmio_read_completed = 0;
		return 1;
	}

	return 0;
}