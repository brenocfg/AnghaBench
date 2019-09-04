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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UD_VECTOR ; 
 int /*<<< orphan*/  X86_CR4_DE ; 
 int /*<<< orphan*/  kvm_queue_exception (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_read_cr4_bits (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

bool kvm_require_dr(struct kvm_vcpu *vcpu, int dr)
{
	if ((dr != 4 && dr != 5) || !kvm_read_cr4_bits(vcpu, X86_CR4_DE))
		return true;

	kvm_queue_exception(vcpu, UD_VECTOR);
	return false;
}