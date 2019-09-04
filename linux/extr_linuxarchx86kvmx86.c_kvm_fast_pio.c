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
 int kvm_fast_pio_in (struct kvm_vcpu*,int,unsigned short) ; 
 int kvm_fast_pio_out (struct kvm_vcpu*,int,unsigned short) ; 
 scalar_t__ kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 

int kvm_fast_pio(struct kvm_vcpu *vcpu, int size, unsigned short port, int in)
{
	int ret;

	if (in)
		ret = kvm_fast_pio_in(vcpu, size, port);
	else
		ret = kvm_fast_pio_out(vcpu, size, port);
	return ret && kvm_skip_emulated_instruction(vcpu);
}