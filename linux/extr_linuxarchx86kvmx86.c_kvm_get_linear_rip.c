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
typedef  unsigned long u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_SREG_CS ; 
 unsigned long get_segment_base (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_64_bit_mode (struct kvm_vcpu*) ; 
 unsigned long kvm_rip_read (struct kvm_vcpu*) ; 

unsigned long kvm_get_linear_rip(struct kvm_vcpu *vcpu)
{
	if (is_64_bit_mode(vcpu))
		return kvm_rip_read(vcpu);
	return (u32)(get_segment_base(vcpu, VCPU_SREG_CS) +
		     kvm_rip_read(vcpu));
}