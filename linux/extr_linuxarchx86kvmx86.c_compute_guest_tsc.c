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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ this_tsc_write; int /*<<< orphan*/  virtual_tsc_shift; int /*<<< orphan*/  virtual_tsc_mult; scalar_t__ this_tsc_nsec; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  pvclock_scale_delta (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 compute_guest_tsc(struct kvm_vcpu *vcpu, s64 kernel_ns)
{
	u64 tsc = pvclock_scale_delta(kernel_ns-vcpu->arch.this_tsc_nsec,
				      vcpu->arch.virtual_tsc_mult,
				      vcpu->arch.virtual_tsc_shift);
	tsc += vcpu->arch.this_tsc_write;
	return tsc;
}