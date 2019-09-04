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
struct vmcs12 {unsigned long guest_cr4; unsigned long cr4_guest_host_mask; } ;
struct TYPE_2__ {unsigned long cr4_guest_owned_bits; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR4_READ_SHADOW ; 
 int /*<<< orphan*/  GUEST_CR4 ; 
 unsigned long vmcs_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long
vmcs12_guest_cr4(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
{
	return
	/*1*/	(vmcs_readl(GUEST_CR4) & vcpu->arch.cr4_guest_owned_bits) |
	/*2*/	(vmcs12->guest_cr4 & vmcs12->cr4_guest_host_mask) |
	/*3*/	(vmcs_readl(CR4_READ_SHADOW) & ~(vmcs12->cr4_guest_host_mask |
			vcpu->arch.cr4_guest_owned_bits));
}