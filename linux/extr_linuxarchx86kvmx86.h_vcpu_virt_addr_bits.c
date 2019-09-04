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
typedef  int u8 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_CR4_LA57 ; 
 scalar_t__ kvm_read_cr4_bits (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 vcpu_virt_addr_bits(struct kvm_vcpu *vcpu)
{
	return kvm_read_cr4_bits(vcpu, X86_CR4_LA57) ? 57 : 48;
}